#pragma once

#include "view/gl_renderer.hpp"

#include "flappy_box/model/paddle.hpp"

#include <GL/freeglut.h>


namespace flappy_box {
namespace view {
class PaddleGlDrawable : public ::view::GlRenderer::Drawable {
public:

	PaddleGlDrawable( const std::shared_ptr< model::Paddle >& );
	virtual ~PaddleGlDrawable();
	virtual void visualize( ::view::GlRenderer&, ::view::GlutWindow& ) override;

private:
	std::shared_ptr< model::Paddle const> _model;

	void updateVBOs();

	void updateRingVBOs();
	void updateBladeVBOs();


	enum {
		_seg0 = 40,
		_seg1 = 15,
		_blade_count = 9,
		_vortex_count = 3,
		_vortex_length = 20,
	};

	GLuint _ring_vbos[3];
	GLuint _blade_vbos[3];
	GLuint _vortex_vbos[_vortex_count];
	GLuint _vortex_color_vbo;

	vec3_type _size;
	double _r0;
	double _r1;


	vec3_type _vortex_dat[_vortex_count][_vortex_length][2];
};
}
}

