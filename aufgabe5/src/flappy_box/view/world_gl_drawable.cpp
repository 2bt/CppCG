#include "flappy_box/view/world_gl_drawable.hpp"

#include <GL/freeglut.h>

#include <algorithm>

using namespace ::flappy_box::view;


WorldGlDrawable::WorldGlDrawable(const std::shared_ptr< ::flappy_box::model::World >& w )
: _model(w) {
 	glGenTextures(1, &_texture);
	glBindTexture(GL_TEXTURE_2D, _texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	static const unsigned char raw[] {
		130, 130, 130, 255, 255, 255, 0, 0,
		255, 255, 255, 130, 130, 130, 0, 0,
	};
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, 2, 2, 0, GL_RGB, GL_UNSIGNED_BYTE, raw);
}

WorldGlDrawable::~WorldGlDrawable() {
 	glDeleteTextures(1, &_texture);
}

void WorldGlDrawable::visualize( ::view::GlRenderer& r, ::view::GlutWindow& win ) {
	float w = _model->getWorldHalfWidth();
	float h = _model->getWorldHalfHeight();
	float dx = w / 30;
	float dy = w / 30;
	float dz = h / 30;
	float s = 0.1;

	float fog[] = { 0.7, 0.7, 0.7, 1 };
	glEnable(GL_FOG);
	glFogfv(GL_FOG_COLOR, fog);
	glFogf(GL_FOG_MODE, GL_LINEAR);
	glFogf(GL_FOG_MODE, GL_EXP2);
	glFogf(GL_FOG_DENSITY, 0.004);
	glFogf(GL_FOG_START, 0);
	glFogf(GL_FOG_END, 100);

	glEnable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _texture);

	glColor3f(0.6, 0.5, 0.4);

	glBegin(GL_QUADS);

	glNormal3f(0, 0, 1);
	for (float x = -w; x < w; x += dx) {
		for (float y = -30; y <= 300; y += dy) {
			glTexCoord2f(x * s, y * s);
			glVertex3f(x, y, -h);
			glTexCoord2f((x + dx) * s, y * s);
			glVertex3f(x + dx, y, -h);
			glTexCoord2f((x + dx) * s, (y + dy) * s);
			glVertex3f(x + dx, y + dy, -h);
			glTexCoord2f(x * s, (y + dy) * s);
			glVertex3f(x, y + dy, -h);
		}
	}
	glNormal3f(0, 0, -1);
	for (float x = -w; x < w; x += dx) {
		for (float y = -30; y <= 300; y += dy) {
			glTexCoord2f(x * s, (y + dy) * s);
			glVertex3f(x, y + dy, h);
			glTexCoord2f((x + dx) * s, (y + dy) * s);
			glVertex3f(x + dx, y + dy, h);
			glTexCoord2f((x + dx) * s, y * s);
			glVertex3f(x + dx, y, h);
			glTexCoord2f(x * s, y * s);
			glVertex3f(x, y, h);
		}
	}
	glNormal3f(1, 0, 0);
	for (float z = -h; z < h; z += dz) {
		for (float y = -30; y <= 300; y += dy) {
			glTexCoord2f(z * s, y * s);
			glVertex3f(-w, y, z);
			glTexCoord2f(z * s, (y + dy) * s);
			glVertex3f(-w, y + dy, z);
			glTexCoord2f((z + dz) * s, (y + dy) * s);
			glVertex3f(-w, y + dy, z + dz);
			glTexCoord2f((z + dz) * s, y * s);
			glVertex3f(-w, y, z + dz);
		}
	}
	glNormal3f(-1, 0, 0);
	for (float z = -h; z < h; z += dz) {
		for (float y = -30; y <= 300; y += dy) {
			glTexCoord2f((z + dz) * s, y * s);
			glVertex3f(w, y, z + dz);
			glTexCoord2f((z + dz) * s, (y + dy) * s);
			glVertex3f(w, y + dy, z + dz);
			glTexCoord2f(z * s, (y + dy) * s);
			glVertex3f(w, y + dy, z);
			glTexCoord2f(z * s, y * s);
			glVertex3f(w, y, z);
		}
	}


	glEnd();

	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);
}

