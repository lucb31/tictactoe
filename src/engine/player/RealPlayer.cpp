#include <engine/player/RealPlayer.hpp>
#include <iostream>

int RealPlayer::getNextMove() {
  if (nextMove > -1) {
    int copiedMove = nextMove;
    // Reset queued move before returning
    nextMove = -1;
    return copiedMove;
  }
  return nextMove;
}
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
    case SDLK_LEFT:
      if (selectedMove > 1) selectedMove--;
      break;
    case SDLK_RIGHT:
      if (selectedMove < 9) selectedMove++;
      break;
    case SDLK_UP:
      if (selectedMove > 3) selectedMove -= 3;
      break;
    case SDLK_DOWN:
      if (selectedMove < 7) selectedMove += 3;
      break;
    // Confirm selected move for next move
    case SDLK_SPACE:
      nextMove = selectedMove;
      break;
    default:
      return;
  }
}