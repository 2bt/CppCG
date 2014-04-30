#pragma once

#include "AbstractVectorN.hpp"
namespace cpp4cg {


template<class T, unsigned int D>
class Vector : public AbstractVectorN<T, D> {
private:
	typedef AbstractVectorN<T, D> Super;
public:
	Vector() : Super() {}
	~Vector() {}
};



template<class T>
class Vector<T, 3> : public AbstractVectorN<T, 3> {
private:
	typedef AbstractVectorN<T, 3> Super;
public:
	Vector() : Super() {}
	~Vector() {}

	Vector(const Super& src) : Super(src) {}

	Vector(T x, T y, T z) { set(x, y, z); }
	T get_x() const { return (*this)[0]; }
	T get_y() const { return (*this)[1]; }
	T get_z() const { return (*this)[2]; }
	void set_x(T v) { (*this)[0] = v; }
	void set_y(T v) { (*this)[1] = v; }
	void set_z(T v) { (*this)[2] = v; }
	void set(T X, T Y, T Z) {
		(*this)[0] = X;
		(*this)[1] = Y;
		(*this)[2] = Z;
	}
	Vector cross(const Vector& rhs) const {
		return Vector(
			(*this)[1]*rhs[2] - (*this)[2]*rhs[1],
			(*this)[2]*rhs[0] - (*this)[0]*rhs[2],
			(*this)[0]*rhs[1] - (*this)[1]*rhs[0]);
	}
};



template<class T>
class Vector<T, 2> : public AbstractVectorN<T, 2> {
private:
	typedef AbstractVectorN<T, 2> Super;
public:
	Vector() : Super() {}
	~Vector() {}

	Vector(const Super& src) : Super(src) {}

	Vector(T x, T y) { set(x, y); }
	T get_x() const { return (*this)[0]; }
	T get_y() const { return (*this)[1]; }
	void set_x(T v) { (*this)[0] = v; }
	void set_y(T v) { (*this)[1] = v; }
	void set(T X, T Y) {
		(*this)[0] = X;
		(*this)[1] = Y;
	}
};



}
