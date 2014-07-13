#include "flappy_box/view/world_gl_drawable.hpp"

#include <GL/freeglut.h>

#include <algorithm>

using namespace ::flappy_box::view;


WorldGlDrawable::WorldGlDrawable(const std::shared_ptr< ::flappy_box::model::World >& w )
: _model(w) {
}

WorldGlDrawable::~WorldGlDrawable() {
}

void WorldGlDrawable::visualize( ::view::GlRenderer& r, ::view::GlutWindow& win ) {
	float w = _model->getWorldHalfWidth();
	float h = _model->getWorldHalfHeight();
	float dx = w / 50;
	float dy = w / 50;
	float dz = h / 50;


	glEnable(GL_LIGHTING);

	glColor3f(0.8, 0.8, 0.8);

	glBegin(GL_QUADS);

	glNormal3f(0, 0, 1);
	for (float x = -w; x < w; x += dx) {
		for (float y = -30; y <= 200; y += dy) {
			glVertex3f(x, y, -h);
			glVertex3f(x + dx, y, -h);
			glVertex3f(x + dx, y + dy, -h);
			glVertex3f(x, y + dy, -h);
		}
	}
	glNormal3f(0, 0, -1);
	for (float x = -w; x < w; x += dx) {
		for (float y = -30; y <= 200; y += dy) {
			glVertex3f(x, y + dy, h);
			glVertex3f(x + dx, y + dy, h);
			glVertex3f(x + dx, y, h);
			glVertex3f(x, y, h);
		}
	}
	glNormal3f(1, 0, 0);
	for (float z = -h; z < h; z += dz) {
		for (float y = -30; y <= 200; y += dy) {
			glVertex3f(-w, y, z);
			glVertex3f(-w, y + dy, z);
			glVertex3f(-w, y + dy, z + dz);
			glVertex3f(-w, y, z + dz);
		}
	}
	glNormal3f(-1, 0, 0);
	for (float z = -h; z < h; z += dz) {
		for (float y = -30; y <= 200; y += dy) {
			glVertex3f(w, y, z + dz);
			glVertex3f(w, y + dy, z + dz);
			glVertex3f(w, y + dy, z);
			glVertex3f(w, y, z);
		}
	}


	glEnd();

	glDisable(GL_LIGHTING);
}

