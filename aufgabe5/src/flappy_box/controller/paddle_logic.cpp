#include "flappy_box/controller/paddle_logic.hpp"
#include <AL/alut.h>
#include <thread>


#include <GL/freeglut.h>

using namespace ::flappy_box::controller;

PaddleLogic::PaddleLogic(const std::shared_ptr< flappy_box::model::Paddle >& b )
: ::controller::Logic::ObjectLogic()
, _model(b) {
}

bool PaddleLogic::advance(::controller::Logic& l, ::controller::InputEventHandler::keyboard_event const& ev) {
	double timestep_sec = l.game_model()->timestep().count();
//	printf("key %d %d\n", ev.key_state, ev.special_key);

	if( ev.key_state == ::controller::InputEventHandler::keyboard_event::key_state_type::KEY_UP)
		_model->setPlayerControl({0, 0, 0});
	else if(ev.special_key == 100) _model->setPlayerControl({-1, 0, 0});
	else if(ev.special_key == 102) _model->setPlayerControl({1, 0, 0});

	double d = 0.9;
	double maxV = 200;
	vec3_type p_alt = _model->position();
	vec3_type v_alt = _model->velocity() * d;
	vec3_type a_alt = _model->acceleration();

	vec3_type a_neu = a_alt * d + _model->playerControl() * 20;
	vec3_type v_neu = v_alt + (a_neu * timestep_sec);
	vec3_type p_neu = p_alt + (v_neu * timestep_sec);

	if(v_neu[0] > maxV) v_neu[0] = maxV;
	if(v_neu[0] < -maxV) v_neu[0] = -maxV;

	if(fabs(p_neu[0]) > _model->maxPosition()[0]) {
		p_neu[0] = p_neu[0] < 0 ? -_model->maxPosition()[0] : _model->maxPosition()[0];
		v_neu[0] = 0;
		a_neu[0] = 0;
	}

	//printf("%f %f %f\n", p_neu[0],p_neu[1],p_neu[2]);
	_model->setPosition(p_neu);
	_model->setVelocity(v_neu);
	_model->setAcceleration(a_neu);
	_model->setAngle(_model->angle() + timestep_sec * 720);

	return false;
}
