#pragma once

#include "math.hpp"

namespace flappy_box::model {

class Box {
public:
	Box() {}

	void pos(vec3_type p) { _pos = p; }
	void vel(vec3_type v) { _val = v; }
	void acc(vec3_type a) { _acc = a; }
	void ang(vec3_type a) { _ang = a; }

	vec3_type pos() { return _pos; }
	vec3_type vel() { return _vel; }
	vec3_type acc() { return _acc; }
	vec3_type ang() { return _ang; }

private:
	vec3_type _pos;
	vec3_type _vel;
	vec3_type _acc;
	vec3_type _ang;

};



}
