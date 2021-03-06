#pragma once

#include "model/game_object.hpp"
#include "math.hpp"

// ATTENTION: NEW CODE!

namespace flappy_box {
namespace model {

class World : public ::model::GameObject {
public:

	World( const std::string& = "World" );

	int playerPoints() const { return _playerPoints; }
	void setPlayerPoints( int pP ) { _playerPoints = pP; }

	int lives() const { return _remainingLives; }
	void setLives( const int& l ) { _remainingLives = l; }

	double getWorldHalfHeight() const { return 30.0; }; /* gibt die halbe Ausdehnung der Spielwelt in z-Richtung zurück */

	double getWorldHalfWidth() const { return 42.0; }; /* gibt die halbe Ausdehnung der Spielwelt in x-Richtung zurück */
	bool shallRestartTheGame() const { return _shallRestartTheGame; }
	void setShallRestartTheGame(bool b) { _shallRestartTheGame = b; }

private:

	int _playerPoints;
	int _remainingLives;
	bool _shallRestartTheGame = true;

};

}
}
