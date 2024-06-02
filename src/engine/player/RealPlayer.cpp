#include <engine/player/RealPlayer.hpp>
#include <iostream>

void RealPlayer::handleKeyPress(SDL_Event* e) {
  switch (e->key.keysym.sym) {
    case SDLK_1:
      nextMove = 1;
      break;
    case SDLK_2:
      nextMove = 2;
      break;
    case SDLK_3:
      nextMove = 3;
      break;
    case SDLK_4:
      nextMove = 4;
      break;
    case SDLK_5:
      nextMove = 5;
      break;
    case SDLK_6:
      nextMove = 6;
      break;
    case SDLK_7:
      nextMove = 7;
      break;
    case SDLK_8:
      nextMove = 8;
      break;
    case SDLK_9:
      nextMove = 9;
      break;
    default:
      return;
  }
}