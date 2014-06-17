#include "view/gl_renderer.hpp"
#include "view/glut_window.hpp"
#include "GL/freeglut.h"

using namespace ::view;

GlRenderer::GlRenderer( std::shared_ptr< model::Game const > const& g )
: _game_model( g ) {}

std::shared_ptr< ::model::Game const > const& GlRenderer::game_model() const {
  return _game_model;
}

GlRenderer::delegate_factory_type& GlRenderer::drawable_factory() {
  return _drawable_factory;
}

GlRenderer::delegate_factory_type const& GlRenderer::drawable_factory() const {
  return _drawable_factory;
}

void GlRenderer::visualize_model( GlutWindow& w ) {
	// 4.3: initialize OpenGL context, call delegates and swap buffers
	//std::cerr << "!! view::GlRenderer::visualize_model: (PARTS ARE) UNIMPLEMENTED." << std::endl;
	glClearColor(0.1, 0.2, 0.3, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(30, w.width() / static_cast<double>(w.height()), 2, 20);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0, -7, 0, 0, 0, 0, 0, 0, 1);
	glutSwapBuffers();
}

void GlRenderer::resize( GlutWindow& win ) {
	glViewport( 0,0, win.width(), win.height() );
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity(); //Reset the camera
	gluPerspective( 45., win.width() / double( win.height() ), .5, 100. );
}
