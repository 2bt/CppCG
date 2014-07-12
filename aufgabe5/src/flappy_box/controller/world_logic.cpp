#include "flappy_box/controller/world_logic.hpp"
#include "flappy_box/model/game_over.hpp"
#include <AL/alut.h>
#include <thread>
#include <iostream>

#include <GL/freeglut.h>

using namespace ::flappy_box::controller;

WorldLogic::WorldLogic(const std::shared_ptr< flappy_box::model::World >& w, bool shallRestartTheGame )
: ::controller::Logic::ObjectLogic()
, _model( w )
, _shallRestartTheGame(shallRestartTheGame)
{ }

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
	auto paddle = std::dynamic_pointer_cast< flappy_box::model::Paddle >(*paddle_it);

	auto world = std::dynamic_pointer_cast< flappy_box::model::World >(*std::find_if(
			l.game_model()->objects().begin(), l.game_model()->objects().end(),
			[](std::shared_ptr< ::model::GameObject> const& p) { return p->name() == "World"; }));

	if (world->lives() > 0) world->setPlayerPoints(world->playerPoints() + 1);
	else {
		auto over = std::make_shared<flappy_box::model::GameOver>("GameOver", world->playerPoints());
		l.game_model()->addGameObject(over);
		paddle->setAlive(false);
	}

	for (auto& obj : l.game_model()->objects()) {
		//if (obj->name() != "Box") continue;
		auto box = std::dynamic_pointer_cast<flappy_box::model::Box>(obj);
		if (!box) continue;
		setForce(box, paddle);

		if (box->position()[2] < paddle->position()[2]) {
			box->setAlive(false);
			world->setLives(world->lives() - 1);
		}
		if (!box->isAlive()) continue;

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
	for (auto& o : l.game_model()->objects()) o->setAlive( false );
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
	box->setMaxPosition({
		_model->getWorldHalfWidth(), 
		_model->getWorldHalfHeight(), 
		0
	});
	box->setSize(1 + rand() / double(RAND_MAX) * 3);
	box->setPosition({
		rand() / double(RAND_MAX) * box->maxPosition()[0] - box->size(),
		0,
		0
	});
	l.game_model()->addGameObject(box);


}

void WorldLogic::setForce( std::shared_ptr< flappy_box::model::Box > & box, std::shared_ptr<flappy_box::model::Paddle > & paddle ) {
  // realisiert die Interaktion zwischen Nutzer-Paddle und den Boxes
}

