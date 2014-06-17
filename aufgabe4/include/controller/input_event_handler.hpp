# pragma once

namespace controller {

class InputEventHandler {
public:

	// 4.1: declare pure-virtual handle function and define struct keyboard_event
	enum {
		SHIFT_ACTIVE = 1,
		CTRL_ACTIVE = 2,
		ALT_ACTIVE = 4
	};
	struct keyboard_event {
		char key;
		int modifyer_mask;
		double mouse_pos[2];
	};
	virtual bool handle(const keyboard_event& e) = 0;

}; // InputEventHandler

} // controller::
