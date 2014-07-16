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


}
