#pragma once

#include <array>
#include <cmath>
#include <error.h>

namespace cpp4cg {


template<typename T, unsigned int D>
class AbstractVectorN {
private:
	std::array<T, D> data;
public:
	typedef T value_type;
	AbstractVectorN() : data {} {}
	AbstractVectorN(const AbstractVectorN& src) : data(src.data) {}
	~AbstractVectorN() {}
	T length() const { return sqrt(dot(*this)); }
	void normalize() {
		T l = length();
		for (T& v : data) v /= l;
	}
	T dot(const AbstractVectorN& rhs) const {
		T s = 0;
		for (int i = 0; i < data.size(); i++) s += data[i] * rhs.data[i];
		return s;
	}
	AbstractVectorN operator+(const AbstractVectorN& rhs) const {
		AbstractVectorN v;
		for (int i = 0; i < data.size(); i++) v.data[i] += data[i] + rhs.data[i];
		return v;
	}
	AbstractVectorN operator-() const {
		AbstractVectorN v;
		for (int i = 0; i < data.size(); i++) v.data[i] = -data[i];
		return v;
	}
	AbstractVectorN operator-(const AbstractVectorN& rhs) const { return *this + -rhs; }
	AbstractVectorN operator*(T rhs) const {
		AbstractVectorN v;
		for (int i = 0; i < data.size(); i++) v.data[i] = data[i] * rhs;
		return v;
	}
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
	AbstractVectorN& operator=(const AbstractVectorN& rhs) { data = rhs.data; return *this; }
	bool operator==(const AbstractVectorN& rhs) {
		AbstractVectorN d = *this - rhs;
		return d.dot(d) <= 0.0001;
	}
};
template<typename T, unsigned int D>
AbstractVectorN<T, D> operator*(T lhs, const AbstractVectorN<T, D>& rhs) { return rhs * lhs; }


}
