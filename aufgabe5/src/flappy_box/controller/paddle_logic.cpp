#include "flappy_box/controller/paddle_logic.hpp"
#include <AL/alut.h>
#include <thread>


#include <GL/freeglut.h>

using namespace ::flappy_box::controller;

PaddleLogic::PaddleLogic(const std::shared_ptr< flappy_box::model::Paddle >& b )
: ::controller::Logic::ObjectLogic()
, _model( b )
{}

bool PaddleLogic::advance( ::controller::Logic& l, ::controller::InputEventHandler::keyboard_event const& ev ) {
	double timestep_sec = l.game_model()->timestep().count();
	//printf("key %d\n", ev.key_state); 
	// TODO irgendwo muss das teil erzeugt werden 
	if( ev.key_state == ::controller::InputEventHandler::keyboard_event::key_state_type::KEY_UP)
		_model->setPlayerControl(vec3_type(0.0, 0.0, 0.0));
	else if(ev.special_key == 1)
		_model->setPlayerControl(vec3_type(-1.0, 0.0, 0.0));
	else if(ev.special_key == 2)
		_model->setPlayerControl(vec3_type(1.0, 0.0, 0.0));

	double d = 0.8;
	double maxV = 100;
	vec3_type p_alt = _model->position();
	vec3_type v_alt = _model->velocity() * d;
	vec3_type a_alt = _model->acceleration();

	vec3_type a_neu = a_alt * d + _model->playerControl();
	vec3_type v_neu = v_alt + (a_neu * timestep_sec);
	vec3_type p_neu = p_alt + (v_neu * timestep_sec);

	if(v_neu[0] > maxV)
		v_neu[0] = maxV;

	if(abs(p_neu[0]) > _model->maxPosition()[0]) {
		p_neu[0] = p_neu[0] < 0 ? -_model->maxPosition()[0] : _model->maxPosition()[0];
	}

	//printf("%f %f %f\n", p_neu[0],p_neu[1],p_neu[2]);
	_model->setPosition(p_neu);
	_model->setVelocity(v_neu);
	_model->setAcceleration(a_neu);

	return false;
}
