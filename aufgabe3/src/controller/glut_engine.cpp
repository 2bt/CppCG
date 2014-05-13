#include <iostream>
#include <stdexcept>
#include <GL/freeglut.h>

#include "glut_engine.hpp"


static void draw() {
	glClearColor(0, 1, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glutSwapBuffers();
}

static void resize(int width, int height) {
	glViewport(0, 0, width, height);
}

static void keyboard(unsigned char key, int x, int y) {
	if (key == 'q') glutLeaveMainLoop();
}


using namespace controller;

GlutEngine::GlutEngine() : Engine() {}
GlutEngine::~GlutEngine() {}

void GlutEngine::init(int argc, char** argv) {
	if (initialized) throw std::logic_error("already initialized");
	std::cout << "GlutEngine::init: checkpoint\n";
	initialized = true;

	glutInit(&argc, argv);
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE,
		GLUT_ACTION_GLUTMAINLOOP_RETURNS);
}

void GlutEngine::run() {
	if (!initialized) throw std::logic_error("not initialized");
	std::cout << "GlutEngine::run: checkpoint\n";

	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(640, 480);
	glutCreateWindow("cpp4cg3-Window");

	glutDisplayFunc(draw);
	glutReshapeFunc(resize);
	glutKeyboardFunc(keyboard);

	glutMainLoop();
}

