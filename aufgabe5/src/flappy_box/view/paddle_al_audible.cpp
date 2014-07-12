#include "flappy_box/view/paddle_al_audible.hpp"

#include <AL/alut.h>
#include <thread>
#include <functional>

#include "math.hpp"

#include "sound_provider.hpp"

using namespace flappy_box::view;

PaddleAlAudible::PaddleAlAudible(std::shared_ptr<flappy_box::model::Paddle> const& p)
: _model(p) {
}


void PaddleAlAudible::auralize( ::view::AlRenderer& renderer ) {
}

