# include "flappy_box/controller/box_object_logic.hpp"
# include <AL/alut.h>
# include <thread>


# include <GL/freeglut.h>

using namespace ::flappy_box::controller;

BoxObjectLogic::BoxObjectLogic(const std::shared_ptr< flappy_box::model::Box >& b )
: ::controller::Logic::ObjectLogic()
, _model(b) {
}

bool BoxObjectLogic::advance( ::controller::Logic& l, ::controller::InputEventHandler::keyboard_event const& ev ) {
	double timestep_sec = l.game_model()->timestep().count();
	vec3_type p_alt = _model->position();
	vec3_type v_alt = _model->velocity();
	vec3_type a_alt = _model->acceleration();

	vec3_type a_grav = vec3_type(0.0, 0.0, -1.5);
	vec3_type f_ext = _model->externalForce();
	double d = 0.8;
	double m = _model->size() * _model->size() * _model->size();

	vec3_type a_ext = f_ext / m;
	vec3_type a_neu = a_alt * d + a_ext + a_grav;

	vec3_type v_neu = v_alt + (a_neu * timestep_sec);
	vec3_type p_neu = p_alt + (v_neu * timestep_sec);

	for (int i = 0; i < p_neu.SizeAtCompileTime; i+=2) { // x z 
		if (fabs(p_neu[i]) > _model->maxPosition()[i]) {
			v_neu[i] *= -d; //spiegeln und dämpfung i
			p_neu[i] = p_neu[i] < 0 ? -_model->maxPosition()[i] : _model->maxPosition()[i];
		}
	}

	_model->setPosition(p_neu);
	_model->setVelocity(v_neu);
	_model->setAcceleration(a_neu);
	_model->setAngle(_model->angle() + timestep_sec * 10);

	return false;
}
