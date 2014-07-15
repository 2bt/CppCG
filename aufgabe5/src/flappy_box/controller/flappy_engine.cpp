#include "flappy_box/controller/flappy_engine.hpp"


#include "flappy_box/model/game_over.hpp"
#include "flappy_box/controller/game_over_logic.hpp"
#include "flappy_box/view/game_over_gl_drawable.hpp"
#include "flappy_box/view/game_over_al_audible.hpp"

#include "flappy_box/model/world.hpp"
#include "flappy_box/controller/world_logic.hpp"
#include "flappy_box/view/world_gl_drawable.hpp"
#include "flappy_box/view/world_al_audible.hpp"

#include "flappy_box/model/paddle.hpp"
#include "flappy_box/controller/paddle_logic.hpp"
#include "flappy_box/view/paddle_gl_drawable.hpp"
#include "flappy_box/view/paddle_al_audible.hpp"

#include "flappy_box/model/box.hpp"
#include "flappy_box/controller/box_object_logic.hpp"
#include "flappy_box/view/box_gl_drawable.hpp"
#include "flappy_box/view/box_al_audible.hpp"

#include "view/glut_window.hpp"

#include <AL/alut.h>



using namespace ::flappy_box::controller;

static std::function<void()> __current_glut_advance_func = [](){ std::cerr << "Warning: Default function called in __current_glut_advance_func." << std::endl; };

FlappyEngine::FlappyEngine( const std::shared_ptr< ::controller::Logic >& l)
: ::controller::GlutEngine(l)
, _al_renderer(std::make_shared< ::view::AlRenderer>(game_model()))
, _gl_renderer(std::make_shared< ::view::GlRenderer>(game_model())) {
}

void FlappyEngine::init( int& argc, char** argv ) {
	GlutEngine::init( argc, argv );
	alutInit( &argc, argv );

	// box
	game_logic()->logic_factory().register_module<flappy_box::model::Box>([](std::shared_ptr<flappy_box::model::Box> const& b) { return std::make_shared<BoxObjectLogic>(b); });
	al_renderer()->audible_factory().register_module<flappy_box::model::Box>([](std::shared_ptr<flappy_box::model::Box> const& b) { return std::make_shared<view::BoxAlAudible>(b); });
	gl_renderer()->drawable_factory().register_module<flappy_box::model::Box>([](std::shared_ptr<flappy_box::model::Box> const& b) { return std::make_shared<view::BoxGlDrawable>(b); });

	// game over
	game_logic()->logic_factory().register_module<flappy_box::model::GameOver>([](std::shared_ptr<flappy_box::model::GameOver> const& o) { return std::make_shared<GameOverLogic>(o); });
	al_renderer()->audible_factory().register_module<flappy_box::model::GameOver>([](std::shared_ptr<flappy_box::model::GameOver> const& o) { return std::make_shared<view::GameOverAlAudible>(o); });
	gl_renderer()->drawable_factory().register_module<flappy_box::model::GameOver>([](std::shared_ptr<flappy_box::model::GameOver> const& o) { return std::make_shared<view::GameOverGlDrawable>(o); });

	// world
	game_logic()->logic_factory().register_module<flappy_box::model::World>([](std::shared_ptr<flappy_box::model::World> const& w) { return std::make_shared<WorldLogic>(w); });
	al_renderer()->audible_factory().register_module<flappy_box::model::World>([](std::shared_ptr<flappy_box::model::World> const& w) { return std::make_shared<view::WorldAlAudible>(w); });
	gl_renderer()->drawable_factory().register_module<flappy_box::model::World>([](std::shared_ptr<flappy_box::model::World> const& w) { return std::make_shared<view::WorldGlDrawable>(w); });

	// paddle
	game_logic()->logic_factory().register_module<flappy_box::model::Paddle>([](std::shared_ptr<flappy_box::model::Paddle> const& p) { return std::make_shared<PaddleLogic>(p); });
	al_renderer()->audible_factory().register_module<flappy_box::model::Paddle>([](std::shared_ptr<flappy_box::model::Paddle> const& p) { return std::make_shared<view::PaddleAlAudible>(p); });
	gl_renderer()->drawable_factory().register_module<flappy_box::model::Paddle>([](std::shared_ptr<flappy_box::model::Paddle> const& p) { return std::make_shared<view::PaddleGlDrawable>(p); });


	// create stuff...
	auto world = std::make_shared<flappy_box::model::World>();
	game_model()->addGameObject(world);

	auto box = std::make_shared< flappy_box::model::Box>();
	box->setSize(20.0);
	box->setAngle(22.5);
	game_model()->addGameObject(box);
}


void FlappyEngine::run() {
	// Create a window and connect it with a view::GlRenderer and an InputEventHandler.
	auto window = std::make_shared< ::view::GlutWindow >( "flappy_box", 1500, 1000, gl_renderer() , shared_from_this() );

	// run game
	GlutEngine::run();
	alutExit();
}

void FlappyEngine::step( ::controller::InputEventHandler::keyboard_event const& ev ) {
	::controller::GlutEngine::step( ev );
	al_renderer()->auralize_model();
	glutPostRedisplay();
}

