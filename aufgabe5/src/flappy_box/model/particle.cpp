# include "flappy_box/model/particle.hpp"

using namespace flappy_box::model;

Particle::Particle(const std::string& n)
: GameObject( true, n ) {

	_velocity[0] = (1 - rand() / float(RAND_MAX) * 2) * 40;
	_velocity[1] = (1 - rand() / float(RAND_MAX) * 2) * 40;
	_velocity[2] = (1 - rand() / float(RAND_MAX) * 2) * 40;
	_hue = 0.2 + rand() / float(RAND_MAX) * 0.8;
}
