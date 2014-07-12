#include "flappy_box/controller/world_logic.hpp"
#include "flappy_box/model/game_over.hpp"
#include <AL/alut.h>
#include <thread>
#include <iostream>

#include <GL/freeglut.h>

using namespace ::flappy_box::controller;

WorldLogic::WorldLogic(const std::shared_ptr< flappy_box::model::World >& w)
: ::controller::Logic::ObjectLogic()
, _model( w )
, _shallRestartTheGame(true) {
}

bool WorldLogic::advance( ::controller::Logic& l, ::controller::InputEventHandler::keyboard_event const& ev ) {
	static double time = 0;
	//double timestep_sec = l.game_model()->timestep().count();

	if(_shallRestartTheGame) restartGame(l);

	using namespace std::chrono;
	steady_clock::time_point now = steady_clock::now();
	duration<double> time_span = duration_cast<duration<double>>(now - _previousTs);
	_previousTs = now;
	time += time_span.count();

	if(time > _timeDelta) {
		time = 0;
		addBoxToGame(l);
	}

	auto paddle_it = std::find_if(l.game_model()->objects().begin(), l.game_model()->objects().end(),
		[](std::shared_ptr< ::model::GameObject> const& p) { return p->name() == "Paddle"; });
	std::shared_ptr<flappy_box::model::Paddle> paddle;
	if (paddle_it != l.game_model()->objects().end()) {
		paddle = std::dynamic_pointer_cast<flappy_box::model::Paddle>(*paddle_it);
	}

	auto world = std::dynamic_pointer_cast< flappy_box::model::World >(*std::find_if(
			l.game_model()->objects().begin(), l.game_model()->objects().end(),
			[](std::shared_ptr< ::model::GameObject> const& p) { return p->name() == "World"; }));

	if (world->lives() > 0) world->setPlayerPoints(world->playerPoints() + 1);
	else if (paddle) {
		auto over = std::make_shared<flappy_box::model::GameOver>("GameOver", world->playerPoints());
		l.game_model()->addGameObject(over);
		paddle->setAlive(false);
	}

	for (auto& obj : l.game_model()->objects()) {
		auto box = std::dynamic_pointer_cast<flappy_box::model::Box>(obj);
		if (!box || !box->isAlive()) continue;

		if (paddle) {
			setForce(box, paddle);

			if (box->position()[2] < paddle->position()[2]) {
				box->setAlive(false);
				world->setLives(world->lives() - 1);
				continue;
			}
		}

		for (auto& obj2 : l.game_model()->objects()) {
			auto box2 = std::dynamic_pointer_cast<flappy_box::model::Box>(obj2);
			if (!box2 || !box2->isAlive() || box == box2) continue;


			auto d = box->position() - box2->position();
			double l = sqrt(d[0] * d[0] + d[1] * d[1] + d[2] * d[2]);
			if (l <= box->size() + box2->size()) {
				box->setAlive(false);
				box2->setAlive(false);
			}

		}
	}

  
	return false;
}


void WorldLogic::restartGame( ::controller::Logic& l ) {

	// invalidate all game objects
	for (auto& o : l.game_model()->objects()) o->setAlive(false);
	_model->setAlive(true);
	_model->setPlayerPoints(0);
	_model->setLives(5);

	// create and configure new paddle object
	auto paddle = std::make_shared<flappy_box::model::Paddle>("Paddle");
	paddle->setSize({ 10.0, 1.0, 2.5 });
	paddle->setPosition({
		0,
		0,
		-_model->getWorldHalfHeight() + paddle->size()[2] * 2
	});
	paddle->setMaxPosition({
		_model->getWorldHalfWidth() - paddle->size()[0] * 0.5,
		0,
		_model->getWorldHalfHeight()
	});
	l.game_model()->addGameObject(paddle);
	_shallRestartTheGame = false;
}

void WorldLogic::addBoxToGame( ::controller::Logic& l ) {

	auto box = std::make_shared<flappy_box::model::Box>();
	box->setSize(1 + rand() / double(RAND_MAX) * 3);

	box->setMaxPosition({
		_model->getWorldHalfWidth() - box->size() * 0.5,
		0,
		_model->getWorldHalfHeight() - box->size() * 0.5
	});
	box->setPosition({
		(rand() / double(RAND_MAX) * 2 - 1) * box->maxPosition()[0],
		0,
		_model->getWorldHalfHeight() - box->size() * 0.5
	});
	l.game_model()->addGameObject(box);
}


void WorldLogic::setForce( std::shared_ptr< flappy_box::model::Box > & box, std::shared_ptr<flappy_box::model::Paddle > & paddle ) {
  // TODO: realisiert die Interaktion zwischen Nutzer-Paddle und den Boxes
}

