#include <iostream>
#include <stdexcept>
#include <memory>
#include <GL/freeglut.h>

#include "glut_engine.hpp"
#include "../view/window.hpp"



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

	std::shared_ptr<view::Window> window(new view::Window(500, 500, "cpp4cg3-window"));

	glutMainLoop();
}

