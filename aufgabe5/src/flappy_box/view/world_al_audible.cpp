#include "flappy_box/view/world_al_audible.hpp"

#include <AL/alut.h>
#include <thread>
#include <functional>

#include "math.hpp"

#include "sound_provider.hpp"

using namespace flappy_box::view;

WorldAlAudible::WorldAlAudible(std::shared_ptr<flappy_box::model::World> const& w)
: _model(w) {
}


void WorldAlAudible::auralize( ::view::AlRenderer& renderer ) {
}

