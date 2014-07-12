#include "flappy_box/view/game_over_al_audible.hpp"

#include <AL/alut.h>
#include <thread>
#include <functional>

#include "math.hpp"

#include "sound_provider.hpp"

using namespace flappy_box::view;

GameOverAlAudible::GameOverAlAudible(std::shared_ptr<flappy_box::model::GameOver> const& o)
: _model(o) {
}


void GameOverAlAudible::auralize( ::view::AlRenderer& renderer ) {
}

