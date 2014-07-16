#include "flappy_box/view/particle_gl_drawable.hpp"

#include <GL/freeglut.h>

#include <algorithm>

using namespace ::flappy_box::view;


ParticleGlDrawable::ParticleGlDrawable(const std::shared_ptr< ::flappy_box::model::Particle>& p)
: _model(p) {

}

ParticleGlDrawable::~ParticleGlDrawable() {
}

void ParticleGlDrawable::visualize(::view::GlRenderer& r, ::view::GlutWindow& w) {
	double timestep_sec = r.game_model()->timestep().count();

	glColor3f(0, _model->hue(), 0);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glPointSize((1 - _model->age()) * 10);

	glBegin(GL_POINTS);
	vec3_type pos = _model->position();
	glVertex3f(pos[0], pos[1], pos[2]);
	glEnd();

	glDisable(GL_BLEND);

}
