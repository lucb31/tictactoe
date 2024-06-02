#include <stdlib.h>

#include <engine/player/AIPlayer.hpp>

void AIPlayer::handleKeyPress(SDL_Event* e) {
  // Queue up random move on Space bar
  if (e->key.keysym.sym == SDLK_SPACE) {
    nextMove = rand() % 9 + 1;
  }
}
