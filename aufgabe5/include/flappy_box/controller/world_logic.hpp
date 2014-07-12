#pragma once

#include "controller/logic.hpp"
#include "flappy_box/model/world.hpp"
#include "flappy_box/model/paddle.hpp"
#include "flappy_box/model/box.hpp"

namespace flappy_box {
namespace controller {

class WorldLogic : public ::controller::Logic::ObjectLogic {
public:
	WorldLogic() = delete;
	WorldLogic( const std::shared_ptr< ::flappy_box::model::World >&);

	virtual bool advance( ::controller::Logic&, ::controller::InputEventHandler::keyboard_event const & ) override;

private:
	void addBoxToGame( ::controller::Logic& l );
	void setForce( std::shared_ptr< flappy_box::model::Box > & box, std::shared_ptr<flappy_box::model::Paddle > & paddle );
	void restartGame( ::controller::Logic& l );


	std::shared_ptr< ::flappy_box::model::World > _model;
	bool _shallRestartTheGame;
	const double _timeDelta = 10;
	std::chrono::steady_clock::time_point _previousTs;
};

}

} // audiophile
