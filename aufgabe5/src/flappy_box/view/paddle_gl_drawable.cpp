#include <algorithm>

#include <GL/glew.h>
#include <GL/freeglut.h>

#include "flappy_box/view/paddle_gl_drawable.hpp"

using namespace ::flappy_box::view;


PaddleGlDrawable::PaddleGlDrawable(const std::shared_ptr< ::flappy_box::model::Paddle >& p)
: _model(p) {

	glGenBuffers(3, _buffers);
	updateVBOs();
}

PaddleGlDrawable::~PaddleGlDrawable() {
	glDeleteBuffers(3, _buffers);
}

void PaddleGlDrawable::updateVBOs() {
	_size = _model->size();

	_r0 = std::max(_model->size()[0], _model->size()[1]) * 0.5;
	_r1 = std::min(_model->size()[2] * 0.5, _r0);

	float v[_seg0 * _seg1 * 3];
	float n[_seg0 * _seg1 * 3];
	unsigned int t[_seg0 * _seg1 * 6];

	float* vp = v;
	float* np = n;
	unsigned int* tp = t;

	for (int s0 = 0; s0 < _seg0; s0++) {
		float a = s0 / float(_seg0) * 2 * M_PI;
		for (int s1 = 0; s1 < _seg1; s1++) {

			float b = s1 / float(_seg1) * 2 * M_PI;

			np[0] = cosf(b) * cosf(a);
			np[1] = cosf(b) * sinf(a);
			np[2] = sinf(b);

			vp[0] = _r0 * cosf(a) + _r1 * np[0];
			vp[1] = _r0 * sinf(a) + _r1 * np[1];
			vp[2] =                 _r1 * np[2];

			tp[0] = s0 * _seg1 + s1;
			tp[1] = ((s0 + 1) % _seg0) * _seg1 + s1;
			tp[2] = s0 * _seg1 + (s1 + 1) % _seg1;
			tp[3] = s0 * _seg1 + (s1 + 1) % _seg1;
			tp[4] = ((s0 + 1) % _seg0) * _seg1 + s1;
			tp[5] = ((s0 + 1) % _seg0) * _seg1 + (s1 + 1) % _seg1;

			vp += 3;
			np += 3;
			tp += 6;
		}
	}


	glBindBuffer(GL_ARRAY_BUFFER, _buffers[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(v), v, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, _buffers[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(n), n, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _buffers[2]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(t), t, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void PaddleGlDrawable::visualize( ::view::GlRenderer& r, ::view::GlutWindow& w ) {
	if (_model->size() != _size) updateVBOs();

	vec3_type pos = _model->position();

	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	float l_pos[] = {
		float(pos[0]),
		float(pos[1] - _r0 * 1.5),
		float(pos[2] + _r1 * 3),
		1
	};
	float l_amb[] = { 0, 0, 0, 1 };
	float l_dif[] = { 1, 1, 1, 1 };
	glLightfv(GL_LIGHT0, GL_POSITION, l_pos);
	glLightfv(GL_LIGHT0, GL_AMBIENT, l_amb);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, l_dif);

	glColor3f(0.6, 0.9, 0.7);

	glPushMatrix();
	glTranslated(pos[0], pos[1], pos[2]);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);

	glBindBuffer(GL_ARRAY_BUFFER, _buffers[0]);
	glVertexPointer(3, GL_FLOAT, 0, NULL);
	glBindBuffer(GL_ARRAY_BUFFER, _buffers[1]);
	glNormalPointer(GL_FLOAT, 0, NULL);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER_ARB, _buffers[2]);
	glDrawElements(GL_TRIANGLES, _seg0 * _seg1 * 6, GL_UNSIGNED_INT, NULL);

	glDisable(GL_LIGHTING);
/*
	glLineWidth(1);
	glColor3f(0, 0, 0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glDrawElements(GL_TRIANGLES, _seg0 * _seg1 * 6, GL_UNSIGNED_INT, NULL);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
*/

	glPopMatrix();

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);


}

