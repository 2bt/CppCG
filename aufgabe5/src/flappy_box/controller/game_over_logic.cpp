#include "flappy_box/controller/game_over_logic.hpp"


using namespace ::flappy_box::controller;
GameOverLogic::GameOverLogic(const std::shared_ptr< model::GameOver >& model)
: _model(model) {
}

bool GameOverLogic::advance( ::controller::Logic& l, ::controller::InputEventHandler::keyboard_event const& ev ) {
	return false;
}
