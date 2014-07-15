#include "flappy_box/view/game_over_al_audible.hpp"

#include <AL/alut.h>
#include <thread>
#include <functional>
#include "math.hpp"

#include "sound_provider.hpp"

using namespace flappy_box::view;

GameOverAlAudible::GameOverAlAudible(std::shared_ptr<flappy_box::model::GameOver> const& o)
: _model(o) {
  _handle = SoundProvider::getInstance()->playSound("laugh.wav", 0.0, 1.0, 1.0, false);
  _x_position = -1.0;
}


void GameOverAlAudible::auralize( ::view::AlRenderer& renderer ) {
//   if(_x_position < 1) {
//     _x_position += 0.1;
//         alSourcef(_handle, AL_POSITION, _x_position);
//   }
}

