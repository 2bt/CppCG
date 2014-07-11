# include "flappy_box/controller/flappy_engine.hpp"

int main( int argc, char** argv ) {
	std::shared_ptr< ::controller::Engine > game_engine( new ::flappy_box::controller::FlappyEngine );

	game_engine->init( argc, argv );
	game_engine->run();

	return 0;
}

// Model:
// Schritt 1 Paddle Klasse impl
// Schritt 2 World Klasse
// Schritt 3 Game Over Klasse
// Controller:
// Schritt 4 advance methode 
// Schritt 5 Bonus Teilaugabe Bewegung in y Richtung TODO
// Schritt 6 Paddle Logic TODO wo wird das erzeugt und advance aufgerufen?
// Schritt 7 World Logic 

