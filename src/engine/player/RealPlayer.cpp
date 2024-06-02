#include <engine/player/RealPlayer.hpp>
#include <iostream>

void RealPlayer::handleKeyPress(SDL_Event* e) {
  if (e->key.keysym.sym == SDLK_1) {
    nextMove = 1;
  }
}