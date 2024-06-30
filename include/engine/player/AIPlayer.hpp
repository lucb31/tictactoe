#pragma once
#include <SDL2/SDL.h>

#include <engine/player/Player.hpp>

class AIPlayer : public Player {
 private:
  Uint32 activeSince = 0;

 public:
  AIPlayer(int& playerValue) : Player{playerValue} {}
  void setActive() { activeSince = SDL_GetTicks(); }
  void setInactive() { activeSince = 0; }
  void handleKeyPress(SDL_Event* e) {}
  int getNextMove();
  int getSelectedMove() { return -1; }
};