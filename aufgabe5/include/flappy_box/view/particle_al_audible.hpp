#pragma once

#include "view/al_renderer.hpp"
#include "flappy_box/model/particle.hpp"

namespace flappy_box {
namespace view {
class ParticleAlAudible : public ::view::AlRenderer::Audible {
public:
	ParticleAlAudible( std::shared_ptr< model::Particle> const& );

	virtual void auralize( ::view::AlRenderer& ) override;

private:
	std::shared_ptr< model::Particle const> _model;

};
}
}
