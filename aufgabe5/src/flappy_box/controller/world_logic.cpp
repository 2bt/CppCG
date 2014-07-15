#include "flappy_box/controller/world_logic.hpp"
#include "flappy_box/model/game_over.hpp"
#include <AL/alut.h>
#include <thread>
#include <iostream>

#include <GL/freeglut.h>

using namespace ::flappy_box::controller;

WorldLogic::WorldLogic(const std::shared_ptr< flappy_box::model::World >& w)
: ::controller::Logic::ObjectLogic()
, _model(w) {
}

bool WorldLogic::advance( ::controller::Logic& l, ::controller::InputEventHandler::keyboard_event const& ev ) {
	static double time = 0;
	double timestep_sec = l.game_model()->timestep().count();

	if(_model->shallRestartTheGame()) restartGame(l);

	time += timestep_sec;
	while (time > _timeDelta) {
		time -= _timeDelta;
		addBoxToGame(l);
	}

	auto paddle_it = std::find_if(l.game_model()->objects().begin(), l.game_model()->objects().end(),
		[](std::shared_ptr< ::model::GameObject> const& p) { return p->name() == "Paddle"; });
	std::shared_ptr<flappy_box::model::Paddle> paddle;
	if (paddle_it != l.game_model()->objects().end()) {
		paddle = std::dynamic_pointer_cast<flappy_box::model::Paddle>(*paddle_it);
	}

	if (_model->lives() > 0) _model->setPlayerPoints(_model->playerPoints() + 1);
	else if (paddle) {
		auto over = std::make_shared<flappy_box::model::GameOver>("GameOver", _model->playerPoints());
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
				_model->setLives(_model->lives() - 1);
				continue;
			}
		}
		else box->setExternalForce({0, 0, 0});

		for (auto& obj2 : l.game_model()->objects()) {
			auto box2 = std::dynamic_pointer_cast<flappy_box::model::Box>(obj2);
			if (!box2 || !box2->isAlive() || box == box2) continue;


			auto d = box->position() - box2->position();
			double l = sqrt(d[0] * d[0] + d[1] * d[1] + d[2] * d[2]);
			if (l <= box->size() * 0.8 + box2->size() * 0.8) {
				box->setAlive(false);
				box2->setAlive(false);
			}

		}
	}

	return false;
}


void WorldLogic::restartGame(::controller::Logic& l) {
	_model->setShallRestartTheGame(false);

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
}

void WorldLogic::addBoxToGame( ::controller::Logic& l ) {

	auto box = std::make_shared<flappy_box::model::Box>();
	box->setSize(2 + rand() / double(RAND_MAX) * 2);

	box->setMaxPosition({
		_model->getWorldHalfWidth() - box->size() * 0.8,
		0,
		_model->getWorldHalfHeight() - box->size() * 0.8
	});
	box->setPosition({
		(rand() / double(RAND_MAX) * 2 - 1) * box->maxPosition()[0],
		0,
		box->maxPosition()[2] * (1 + rand() / double(RAND_MAX)) * 0.5
	});
	box->setAngle(rand() / double(RAND_MAX) * 360);
	l.game_model()->addGameObject(box);
}


void WorldLogic::setForce(std::shared_ptr<flappy_box::model::Box>& box, std::shared_ptr<flappy_box::model::Paddle>& paddle) {
	vec3_type b = box->position();
	vec3_type p = paddle->position();
	double w = paddle->size()[0];
	vec3_type n = vec3_type(0, 0, 1);
	vec3_type f;
	if (b[0] < p[0] - w)		f = b - (p - vec3_type(w, 0, 0));
	else if (b[0] > p[0] + w)	f = b - (p + vec3_type(w, 0, 0));
	else						f = n;
	f.normalize();
	f *= powf(n.dot(f), 5);
	double s = box->size();
	f *= 10 * s * s;

	box->setExternalForce(f);
}




