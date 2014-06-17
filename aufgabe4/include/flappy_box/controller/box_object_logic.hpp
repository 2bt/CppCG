#pragma once

#include "flappy_box/model/box.hpp"
#include "contoller/logic.hpp"

namespace flappy_box::controller {

struct BoxObjectLogic : public controller::Logic::ObjectLogic {
	virtual bool advance( Logic&, InputEventHandler::keyboard_event const& ) {

		return true;
	}


};



}

