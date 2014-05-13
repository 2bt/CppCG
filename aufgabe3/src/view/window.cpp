#include <cstdio>
#include <GL/freeglut.h>
#include "window.hpp"

using namespace view;

Window::Window(size_t width, size_t height, const std::string& name) {
	_width = width;
	_height = height;
	_name = name;
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(width, height);
	_glut_win_id = glutCreateWindow(name.c_str());
	glutSetWindowData(this);
	glutDisplayFunc(glutDisplay);
	glutReshapeFunc(glutReshape);
	glutKeyboardFunc(glutKeyboard);
}

Window::~Window() {
}


void Window::invalidate() {
	// TODO
}

bool Window::display() {
	glClearColor(0, 1, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	return false;
}

void Window::reshape() {
	glViewport(0, 0, _width, _height);
}

void Window::keyboard(unsigned char key, int x, int y) {
	if (key == 'q') glutLeaveMainLoop();
}

void Window::ensureCurrent() const {
	glutSetWindow(_glut_win_id);
}


void Window::glutDisplay() {
	Window* w = static_cast<Window*>(glutGetWindowData());
	if (w && w->_glut_win_id && w->_glut_win_id == glutGetWindow()) {
		w->display();
		glutSwapBuffers();
	}
}

void Window::glutReshape(int width, int height) {
	Window* w = static_cast<Window*>(glutGetWindowData());
	if (w && w->_glut_win_id && w->_glut_win_id == glutGetWindow()) {
		w->_width = width;
		w->_height = height;
		w->reshape();
	}
}

void Window::glutKeyboard(unsigned char key, int x, int y) {
	Window* w = static_cast<Window*>(glutGetWindowData());
	if (w && w->_glut_win_id && w->_glut_win_id == glutGetWindow()) {
		w->keyboard(key, x, y);
	}
}


