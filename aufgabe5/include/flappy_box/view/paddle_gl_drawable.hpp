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

	GLuint _ring_vbos[3];
	GLuint _blade_vbos[3];
	vec3_type _size;
	double _r0;
	double _r1;
	const int _seg0 = 40;
	const int _seg1 = 15;
	const int _blade_count = 9;
	double _angle;
};
}
}

