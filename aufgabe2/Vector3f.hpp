#pragma once

#include <array>
#include <cmath>
#include <error.h>

namespace cpp4cg {


class Vector3f {
private:
	union {
		std::array<float, 3> data;
		struct { float x, y, z; };
	};
public:
	Vector3f() : data {} {}
	Vector3f(const Vector3f& src) : data(src.data) {}
	Vector3f(float x, float y, float z) : x(x), y(y), z(z) {}
	~Vector3f() {}
	float get_x() const { return x; }
	float get_y() const { return y; }
	float get_z() const { return z; }
	void set_x(float v) { x = v; }
	void set_y(float v) { y = v; }
	void set_z(float v) { z = v; }
	void set(float X, float Y, float Z) { x = X; y = Y; z = Z; }
	float length() const { return sqrt(dot(*this)); }
	void normalize() { float f = 1 / length(); x *= f; y *= f; z *= f; }
	float dot(const Vector3f& rhs) const { return x*rhs.x + y*rhs.y + z*rhs.z; }
	Vector3f cross(const Vector3f& rhs) const {
		return Vector3f(y*rhs.z - z*rhs.y, z*rhs.x - x*rhs.z, x*rhs.y - y*rhs.x);
	}
	Vector3f operator+(const Vector3f& rhs) const {
		return Vector3f(x+rhs.x, y+rhs.y, z+rhs.z);
	}
	Vector3f operator-() const { return Vector3f(-x, -y, -z); }
	Vector3f operator-(const Vector3f& rhs) const { return *this + -rhs; }
	Vector3f operator*(float rhs) const { return Vector3f(x*rhs, y*rhs, z*rhs); }
	float& operator[](int idx) {
		if (idx < 0 || idx >= static_cast<int>(data.size())) {
			error(-1, 0, "index out of bounds");
		}
		return data[idx];
	}
	const float& operator[](int idx) const {
		if (idx < 0 || idx >= static_cast<int>(data.size())) {
			error(-1, 0, "index out of bounds");
		}
		return data[idx];
	}
	Vector3f& operator=(const Vector3f& rhs) { if (&rhs != this) data = rhs.data; return *this; }
	bool operator==(const Vector3f& rhs) {
		Vector3f d = *this - rhs;
		return d.dot(d) <= 0.0001;
	}
};
Vector3f operator*(float lhs, const Vector3f& rhs) { return rhs * lhs; }


}
