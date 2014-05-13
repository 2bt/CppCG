#include <cstdio>
#include <GL/freeglut.h>
#include "demo_window.hpp"

using namespace view;

bool DemoWindow::display() {
	glClearColor(0.1, 0.2, 0.3, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// TODO...
	return false;
}

