#pragma once

#include "model/game_object.hpp"
#include "math.hpp"

// ATTENTION: NEW CODE!

namespace flappy_box {

namespace model {
class Particle : public ::model::GameObject {
public:

	Particle(const std::string& = "Particle");

	const vec3_type& position() const { return _position; }
	void setPosition( const vec3_type& p ) { _position = p; }

	double size() const { return _size; }
	void setSize( double s ) { _size = s; }

	double age() const { return _age; }
	void setAge( double a ) { _age = a; }


private:
	double                _size; // same size in every direction
	vec3_type         _position;
	vec3_type         _velocity;
	double                 _age = 0;
};

}
}
