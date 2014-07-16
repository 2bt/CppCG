#pragma once

#include "view/gl_renderer.hpp"

#include "flappy_box/model/particle.hpp"

#include <GL/freeglut.h>

namespace flappy_box {
namespace view {
class ParticleGlDrawable : public ::view::GlRenderer::Drawable {
public:

	ParticleGlDrawable( const std::shared_ptr< model::Particle>& );
	virtual ~ParticleGlDrawable();
	virtual void visualize( ::view::GlRenderer&, ::view::GlutWindow& ) override;

private:
	std::shared_ptr< model::Particle const> _model;
};
}
}
