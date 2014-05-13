#include <cstdio>
#include <GL/freeglut.h>
#include "demo_window.hpp"

using namespace view;

bool DemoWindow::display() {
	glClearColor(0.1, 0.2, 0.3, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(30, width() / static_cast<double>(height()), 2, 20);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0, -7, 0, 0, 0, 0, 0, 0, 1);

	auto dur = start_time - std::chrono::steady_clock::now();
	auto s = std::chrono::duration_cast<std::chrono::duration<float>>(dur);
	float ang = 360 / 5 * s.count();
	glRotatef(ang, 0, 0, 1);

	glColor3f(0.75, 0.75, 0.75);
	glBegin(GL_LINES);

	glVertex3f( 1,  1,  1);
	glVertex3f(-1,  1,  1);
	glVertex3f( 1, -1,  1);
	glVertex3f(-1, -1,  1);
	glVertex3f( 1, -1, -1);
	glVertex3f(-1, -1, -1);
	glVertex3f( 1,  1, -1);
	glVertex3f(-1,  1, -1);

	glVertex3f( 1,  1,  1);
	glVertex3f( 1, -1,  1);
	glVertex3f(-1,  1,  1);
	glVertex3f(-1, -1,  1);
	glVertex3f(-1,  1, -1);
	glVertex3f(-1, -1, -1);
	glVertex3f( 1,  1, -1);
	glVertex3f( 1, -1, -1);

	glVertex3f( 1,  1,  1);
	glVertex3f( 1,  1, -1);
	glVertex3f(-1,  1,  1);
	glVertex3f(-1,  1, -1);
	glVertex3f(-1, -1,  1);
	glVertex3f(-1, -1, -1);
	glVertex3f( 1, -1,  1);
	glVertex3f( 1, -1, -1);

	glEnd();

	return true;
}

