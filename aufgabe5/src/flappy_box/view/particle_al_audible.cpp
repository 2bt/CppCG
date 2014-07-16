#include "flappy_box/view/particle_al_audible.hpp"

#include <AL/alut.h>
#include <thread>
#include <functional>

#include "math.hpp"

#include "sound_provider.hpp"

using namespace flappy_box::view;

ParticleAlAudible::ParticleAlAudible(std::shared_ptr<flappy_box::model::Particle> const& p)
: _model(p) {
}


void ParticleAlAudible::auralize( ::view::AlRenderer& renderer ) {
}
