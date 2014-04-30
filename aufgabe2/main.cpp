#include <cstdio>

typedef float real;

#ifdef A1
#include "Vector3f.hpp"
#endif
#ifdef A2
#include "Vector3.hpp"
namespace cpp4cg { typedef cpp4cg::Vector3<real> Vector3f; }
#endif
#ifdef A3
#include "VectorN.hpp"
namespace cpp4cg { typedef cpp4cg::Vector<real, 3> Vector3f; }
void print_vector(const cpp4cg::Vector<real, 2>& v) {
	printf("(%.1f, %.1f)\n", v[0], v[1]);
}
#endif

void print_vector(const cpp4cg::Vector3f& v) {
	printf("(%.1f, %.1f, %.1f)\n", v[0], v[1], v[2]);
}

using namespace cpp4cg;
int main(int argc, char** argv) {
	printf("Hello, world!\n");

	Vector3f v1(1, 2, 3);
	print_vector(v1);
	printf("len: %f\n", v1.length());
	v1.normalize();
	print_vector(v1);
	printf("len: %f (Erwartet: 1)\n", v1.length());

	Vector3f v2(1, 0, 0);

	Vector3f v3(v1.cross(v2));
	v3.normalize();
	print_vector(v3);

	v1 = v2.cross(v3);
	print_vector(v1);

	printf("len: %f (Erwartet: 1)\n", v1.length());
	printf("len: %f (Erwartet: 1)\n", v2.length());
	printf("len: %f (Erwartet: 1)\n", v3.length());

	printf("test: %f (Erwartet: 0)\n", v1.dot(v2));
	printf("test: %f (Erwartet: 0)\n", v1.dot(v3));
	printf("test: %f (Erwartet: 0)\n", v2.dot(v1));
	printf("test: %f (Erwartet: 0)\n", v2.dot(v3));
	printf("test: %f (Erwartet: 0)\n", v3.dot(v1));
	printf("test: %f (Erwartet: 0)\n", v3.dot(v2));

	// Die Vektoren v1, v2 und v3 sind zueinander orthogonal

	Vector3f v4(3.14159265359f, 2.71828182846f, 42.f);
	print_vector(v4);

	real s1 = v4.dot(v1);
	real s2 = v4.dot(v2);
	real s3 = v4.dot(v3);

	// Die Skalare s1, s2 und s3 sind Koordinaten für die Basis (v1, v2, v3)

	printf("s1: %f\n", s1);
	printf("s2: %f\n", s2);
	printf("s3: %f\n", s3);

	Vector3f v5 = s1 * v1 + s2 * v2 + s3 * v3;
	print_vector(v5);

	printf("All is %s\n", (v4 == v5) ? "right" : "wrong");

	return 0;
}



