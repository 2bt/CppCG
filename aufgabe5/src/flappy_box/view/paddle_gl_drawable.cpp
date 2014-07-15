#include <algorithm>

#include <GL/glew.h>
#include <GL/freeglut.h>

#include "flappy_box/view/paddle_gl_drawable.hpp"

using namespace ::flappy_box::view;


PaddleGlDrawable::PaddleGlDrawable(const std::shared_ptr< ::flappy_box::model::Paddle >& p)
: _model(p) {
	glGenBuffers(3, _ring_vbos);
	glGenBuffers(3, _blade_vbos);
	glGenBuffers(_vortex_count, _vortex_vbos);
	glGenBuffers(1, &_vortex_color_vbo);
	updateVBOs();



	for (int v = 0; v < _vortex_count; v++) {

		glBindBuffer(GL_ARRAY_BUFFER, _vortex_vbos[v]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * _vortex_length * 2 * 3, NULL, GL_DYNAMIC_DRAW);

		for (int i = 0; i < _vortex_length; i++) {
			_vortex_dat[v][i][0] = _model->position();
			_vortex_dat[v][i][1] = _model->position();
		}
	}
}

PaddleGlDrawable::~PaddleGlDrawable() {
	glDeleteBuffers(3, _ring_vbos);
	glDeleteBuffers(3, _blade_vbos);
	glDeleteBuffers(_vortex_count, _vortex_vbos);
	glDeleteBuffers(1, &_vortex_color_vbo);
}

void PaddleGlDrawable::updateRingVBOs() {
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

	glBindBuffer(GL_ARRAY_BUFFER, _ring_vbos[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(v), v, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, _ring_vbos[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(n), n, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ring_vbos[2]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(t), t, GL_STATIC_DRAW);
}


static vec3_type calc_normal(vec3_type a, vec3_type b, vec3_type c) {
	vec3_type ab = b - a;
	vec3_type ac = c - a;
	return ab.cross(ac).normalized();
}


void PaddleGlDrawable::updateBladeVBOs() {
	float v[_blade_count * 9];
	float n[_blade_count * 9];
	unsigned int t[_blade_count * 3];

	float* vp = v;
	float* np = n;
	unsigned int* tp = t;

	for (int c = 0; c < _blade_count; c++) {
		float a1 = (c - 0.3) / float(_blade_count) * 2 * M_PI;
		float a2 = (c + 0.3) / float(_blade_count) * 2 * M_PI;

		vp[0] = vp[1] = vp[2] = 0;

		vp[3] = (_r0 - _r1) * cosf(a1);
		vp[4] = (_r0 - _r1) * sinf(a1);
		vp[5] = _r1;

		vp[6] = (_r0 - _r1) * cosf(a2);
		vp[7] = (_r0 - _r1) * sinf(a2);
		vp[8] = -_r1;

		vec3_type n = calc_normal(
			{ vp[0], vp[1], vp[2] },
			{ vp[3], vp[4], vp[5] },
			{ vp[6], vp[7], vp[8] }
		);
		for (int i = 0; i < 3; i++) {
			np[0] = n[0];
			np[1] = n[1];
			np[2] = n[2];
			np += 3;
		}

		tp[0] = c * 3 + 0;
		tp[1] = c * 3 + 1;
		tp[2] = c * 3 + 2;

		vp += 9;
		tp += 3;
	}

	glBindBuffer(GL_ARRAY_BUFFER, _blade_vbos[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(v), v, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, _blade_vbos[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(n), n, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _blade_vbos[2]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(t), t, GL_STATIC_DRAW);

}


void PaddleGlDrawable::updateVBOs() {
	_size = _model->size();

	_r0 = std::max(_model->size()[0], _model->size()[1]) * 0.5;
	_r1 = std::min(_model->size()[2] * 0.5, _r0);

	updateRingVBOs();
	updateBladeVBOs();

	float c[_vortex_length * 2 * 4];
	float* cp = c;
	for (int i = 0; i < _vortex_length; i++) {
		for (int j = 0; j < 2; j++) {
			cp[0] = cp[1] = cp[2] = 1;
			float f = sinf(M_PI * i / float(_vortex_length - 1));
			cp[3] = 0.25 * f * f;
			cp += 4;
		}
	}
	glBindBuffer(GL_ARRAY_BUFFER, _vortex_color_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(c), c, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void PaddleGlDrawable::visualize( ::view::GlRenderer& r, ::view::GlutWindow& w ) {
	if (_model->size() != _size) updateVBOs();

	vec3_type pos = _model->position();
	float ang = _model->angle();

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


	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);


	glPushMatrix();
	glTranslated(pos[0], pos[1], pos[2]);


	glColor3f(0.6, 0.9, 0.7);
	glBindBuffer(GL_ARRAY_BUFFER, _ring_vbos[0]);
	glVertexPointer(3, GL_FLOAT, 0, NULL);
	glBindBuffer(GL_ARRAY_BUFFER, _ring_vbos[1]);
	glNormalPointer(GL_FLOAT, 0, NULL);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER_ARB, _ring_vbos[2]);
	glDrawElements(GL_TRIANGLES, _seg0 * _seg1 * 6, GL_UNSIGNED_INT, NULL);

	glRotated(ang, 0, 0, 1);
	glDisable(GL_CULL_FACE);
	glColor3f(0.6, 0.7, 0.9);
	glBindBuffer(GL_ARRAY_BUFFER, _blade_vbos[0]);
	glVertexPointer(3, GL_FLOAT, 0, NULL);
	glBindBuffer(GL_ARRAY_BUFFER, _blade_vbos[1]);
	glNormalPointer(GL_FLOAT, 0, NULL);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER_ARB, _blade_vbos[2]);
	glDrawElements(GL_TRIANGLES, _blade_count * 3, GL_UNSIGNED_INT, NULL);
	glEnable(GL_CULL_FACE);


	glDisable(GL_LIGHTING);

	glPopMatrix();


	// render vortices
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	glDepthMask(GL_FALSE);

	glDisableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glBindBuffer(GL_ARRAY_BUFFER, _vortex_color_vbo);
	glColorPointer(4, GL_FLOAT, 0, NULL);
	glColor3f(1, 1, 1);

	double timestep_sec = r.game_model()->timestep().count();
	float vortex_speed = 100;
	float air_vortex_band_width = 1;

	for (int v = 0; v < _vortex_count; v++) {

		for (int t = _vortex_length - 1; t > 0; --t) {
			_vortex_dat[v][t][0] = _vortex_dat[v][t - 1][0] + vec3_type(0, 0, timestep_sec * vortex_speed);
			vec3_type d = _vortex_dat[v][t - 1][1] - _vortex_dat[v][t - 1][0];
			d[2] = 0;
			_vortex_dat[v][t][1] = _vortex_dat[v][t][0] + d * 1.075;
		}
		_vortex_dat[v][0][0] = pos;
		_vortex_dat[v][0][1] = pos + vec3_type(
			_r0 * cosf((ang + v / float(_vortex_count) * 360) / 180 * M_PI),
			0,
			_r0 * sinf((ang + v / float(_vortex_count) * 360) / 180 * M_PI));


		glBindBuffer(GL_ARRAY_BUFFER, _vortex_vbos[v]);
		float* vp = (float*) glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
		for (int t = 0; t < _vortex_length; t++) {
			vec3_type p = _vortex_dat[v][t][1];
			p[0] -= 0.5 * air_vortex_band_width;
			vp[0] = p[0];
			vp[1] = p[1];
			vp[2] = p[2];
			p[0] += air_vortex_band_width;
			vp[3] = p[0];
			vp[4] = p[1];
			vp[5] = p[2];
			vp += 6;
		}

		glUnmapBuffer(GL_ARRAY_BUFFER);
		glVertexPointer(3, GL_FLOAT, 0, NULL);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, _vortex_length * 2);

	}


	glDepthMask(GL_TRUE);
	glDisable(GL_BLEND);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);


}

