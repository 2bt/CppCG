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
			world->setLives(world->lives() -1);
		}

		
	}

  // p;
//   for(auto it = l.game_model()->objects().begin(); it != l.game_model()->objects().end(); it++) {
//     if(it->name() ==  "Paddle") {
// 	auto p = dynamic_cast< ::flappy_box::model::Paddle >(it->get());
// 	break;
//     }
//   }
  
  
  
  return false;
}


void WorldLogic::restartGame( ::controller::Logic& l ) {
  // setzt Spielobjekte zurück und startet das Spiel neu
}
  
void WorldLogic::addBoxToGame( ::controller::Logic& l ) {
  // fügt dem Spiel eine neues Spielobjekt vom Typ flappy_box::model::Box hinzu
}

void WorldLogic::setForce( std::shared_ptr< flappy_box::model::Box > & box, std::shared_ptr<flappy_box::model::Paddle > & paddle ) {
  // realisiert die Interaktion zwischen Nutzer-Paddle und den Boxes
}

