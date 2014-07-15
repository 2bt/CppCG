#include "flappy_box/view/world_al_audible.hpp"
#include<AL/alut.h>
#include<thread>
#include<functional>
#include "sound_provider.hpp"

using namespace flappy_box::view;

ALuint _beatHandle;
ALuint _snythHandle;

WorldAlAudible::WorldAlAudible(std::shared_ptr<flappy_box::model::World> const& w)
: _model(w) {
  _beatHandle  = SoundProvider::getInstance()->playSound("beat.wav", 0.0, 0.3, 1.0, true);
  _snythHandle = SoundProvider::getInstance()->playSound("synth.wav", 0.0, 0.5, 0.5, true);
}


void WorldAlAudible::auralize( ::view::AlRenderer& renderer ) {
  bool alive = true;
  for (auto& obj : renderer.game_model()->objects()) {
    if(obj->name() == "GameOver")
      alive = false;
  }
  if (alive) {
    int points = _model->playerPoints();
    //alSourcef(_beatHandle, AL_GAIN, sin(points/100.0));
    float pitch = 0.5;
    if(points > 100)
      pitch = 1.0;
    if(points > 1000)
      pitch = 2.0;
    alSourcef(_snythHandle, AL_PITCH, pitch); // ((points/40)%2 == 0 ? 2.0 : 1.0)
  } else {
      alSourceStop(_beatHandle);
      alSourceStop(_snythHandle);
  }
}

