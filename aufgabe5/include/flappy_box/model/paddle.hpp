#pragma once
#include <model/game_object.hpp>
#include <math.hpp>


namespace flappy_box {
namespace model {

class Paddle : public ::model::GameObject {
public:
	Paddle( const std::string& = "Paddle" );

	const vec3_type& position() const { return _position; }
	void setPosition(vec3_type position) { _position = position; }

	const vec3_type& maxPosition() const { return _maxPosition; }
	void setMaxPosition(vec3_type position) { _maxPosition = position; }

	const vec3_type& acceleration() const { return _acceleration; }
	void setAcceleration(vec3_type acceleration) { _acceleration = acceleration; }

	const vec3_type& velocity() const { return _velocity; }
	void setVelocity(vec3_type velocity) { _velocity = velocity; }

	const vec3_type& size() const { return _size; }
	void setSize(vec3_type size) { _size = size; }

	const vec3_type& playerControl() const { return _playerControl; }
	void setPlayerControl(vec3_type playerControl) { _playerControl = playerControl; }
private:
	vec3_type _position;
	vec3_type _maxPosition;
	vec3_type _velocity;
	vec3_type _acceleration;
	vec3_type _size;
	vec3_type _playerControl;
};

}
}
