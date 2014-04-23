#pragma once

#include <array>
#include <cmath>
#include <error.h>

namespace cpp4cg {


template<typename T>
class Vector3 {
private:
	union {
		std::array<T, 3> data;
		struct { T x, y, z; };
	};
public:
	typedef T value_type;
	Vector3() : data {} {}
	Vector3(const Vector3& src) : data(src.data) {}
	Vector3(T x, T y, T z) : x(x), y(y), z(z) {}
	~Vector3() {}
	T get_x() const { return x; }
	T get_y() const { return y; }
	T get_z() const { return z; }
	void set_x(T v) { x = v; }
	void set_y(T v) { y = v; }
	void set_z(T v) { z = v; }
	void set(T X, T Y, T Z) { x = X; y = Y; z = Z; }
	T length() const { return sqrt(dot(*this)); }
	void normalize() { T l = length(); x /= l; y /= l; z /= l; }
	T dot(const Vector3& rhs) const { return x*rhs.x + y*rhs.y + z*rhs.z; }
	Vector3 cross(const Vector3& rhs) const {
		return Vector3(y*rhs.z - z*rhs.y, z*rhs.x - x*rhs.z, x*rhs.y - y*rhs.x);
	}
	Vector3 operator+(const Vector3& rhs) const {
		return Vector3(x+rhs.x, y+rhs.y, z+rhs.z);
	}
	Vector3 operator-() const { return Vector3(-x, -y, -z); }
	Vector3 operator-(const Vector3& rhs) const { return *this + -rhs; }
	Vector3 operator*(T rhs) const { return Vector3(x*rhs, y*rhs, z*rhs); }
	T& operator[](int idx) {
		if (idx < 0 || idx >= static_cast<int>(data.size())) {
			error(-1, 0, "index out of bounds");
		}
		return data[idx];
	}
	const T& operator[](int idx) const {
		if (idx < 0 || idx >= static_cast<int>(data.size())) {
			error(-1, 0, "index out of bounds");
		}
		return data[idx];
	}
	Vector3& operator=(const Vector3& rhs) { data = rhs.data; return *this; }
	bool operator==(const Vector3& rhs) {
		Vector3 d = *this - rhs;
		return d.dot(d) < 0.0001;
	}
};
template<typename T>
Vector3<T> operator*(T lhs, const Vector3<T>& rhs) { return rhs * lhs; }


}
