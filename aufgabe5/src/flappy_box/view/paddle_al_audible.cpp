#include "flappy_box/view/paddle_al_audible.hpp"

#include <AL/alut.h>
#include <thread>
#include <functional>

#include "math.hpp"

#include "sound_provider.hpp"

using namespace flappy_box::view;

PaddleAlAudible::PaddleAlAudible(std::shared_ptr<flappy_box::model::Paddle> const& p)
: _model(p) {
  _alPaddleBuffer = alutCreateBufferWaveform(ALUT_WAVEFORM_SINE, 100, 0, 1);
   alGenSources((ALsizei)1, &_alPaddleSource);
   alSourcei (_alPaddleSource, AL_BUFFER, _alPaddleBuffer);
   alSourcef(_alPaddleSource, AL_GAIN, 1.0);
   alSourcei(_alPaddleSource, AL_LOOPING, AL_TRUE);
   alSourcePlay(_alPaddleSource);
}


void PaddleAlAudible::auralize( ::view::AlRenderer& renderer ) {
  //_alPaddleSource
  //_alPaddleBuffer alSource3f()
  
  if(_model->isAlive()) {
    auto pos = _model->position();
    auto max = _model->maxPosition();
    alSourcef(_alPaddleSource, AL_POSITION, pos[0] / max[0]);
    auto vel = fabs(_model->velocity()[0]) / 300;
    alSourcef(_alPaddleSource, AL_PITCH, vel+0.5);
  } else {
    alSourceStop(_alPaddleSource);
    alDeleteSources((ALsizei)1, &_alPaddleSource);
    alDeleteBuffers((ALsizei)1, &_alPaddleBuffer);
  }  
}

