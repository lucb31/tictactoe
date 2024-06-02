#include <SDL2/SDL.h>
#include <stdlib.h>

#include <engine/player/AIPlayer.hpp>

// Todo Magic number 2000 (AI timeout)
// Todo Magic number 9 (board dimensions)
int AIPlayer::getNextMove() {
  // Wait for 2s until making an AI move
  if (SDL_GetTicks() > activeSince + 2000) {
    return rand() % 9 + 1;
  }
  return -1;
}
