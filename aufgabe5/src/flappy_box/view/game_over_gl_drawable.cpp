#include "flappy_box/view/game_over_gl_drawable.hpp"

#include <GL/freeglut.h>

#include <algorithm>

using namespace ::flappy_box::view;


GameOverGlDrawable::GameOverGlDrawable(const std::shared_ptr< ::flappy_box::model::GameOver >& o)
: _model(o) {
}

GameOverGlDrawable::~GameOverGlDrawable() {
}

void GameOverGlDrawable::visualize( ::view::GlRenderer& r, ::view::GlutWindow& w ) {
}

