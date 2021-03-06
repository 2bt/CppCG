# include "controller/logic.hpp"

using namespace ::controller;

Logic::Logic( const std::shared_ptr< ::model::Game >& g ) : _model( g ) {}

bool Logic::advance_model( const ::controller::InputEventHandler::keyboard_event& ev ) {
	// 4.3: set current timestamp in model and call delegates
	//std::cerr << "!! controller::Logic::advance_model: (PARTS ARE) UNIMPLEMENTED." << std::endl; 
	_model->setTimestamp(std::chrono::steady_clock::now());


	return false;
}
