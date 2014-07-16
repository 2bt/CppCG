# include "flappy_box/controller/particle_logic.hpp"
# include <AL/alut.h>
# include <thread>


# include <GL/freeglut.h>

using namespace ::flappy_box::controller;

ParticleLogic::ParticleLogic(const std::shared_ptr< flappy_box::model::Particle>& p )
: ::controller::Logic::ObjectLogic()
, _model(p) {
}

bool ParticleLogic::advance( ::controller::Logic& l, ::controller::InputEventHandler::keyboard_event const& ev ) {
	double timestep_sec = l.game_model()->timestep().count();
	double age = _model->age();
	if (age > 1) _model->setAlive(false);
	_model->setAge(age + timestep_sec);


	_model->setPosition(_model->position()  + _model->velocity() * timestep_sec);
	return false;
}
