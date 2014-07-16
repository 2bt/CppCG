# pragma once

# include "controller/logic.hpp"
# include "flappy_box/model/particle.hpp"

namespace flappy_box {
namespace controller {

class ParticleLogic : public ::controller::Logic::ObjectLogic {
	public:
		ParticleLogic() = delete;
		ParticleLogic( const std::shared_ptr< model::Particle >& );

		virtual bool advance( ::controller::Logic&, ::controller::InputEventHandler::keyboard_event const & ) override;

	private:
		std::shared_ptr<model::Particle> _model;
};

}
}
