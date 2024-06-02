#pragma once
#include <SDL2/SDL.h>

class Player {
  // Value that will be assigned to the board to represent this player
  const int playerValue;

 protected:
  Uint32 activeSince = 0;

 public:
  Player(const int& playerValue) : playerValue(playerValue) {}
  int getValue() { return playerValue; }
  void setActive() { activeSince = SDL_GetTicks(); }
  void setInactive() { activeSince = 0; }
  // Returns position (1-9) of next field to occupy
  virtual int getNextMove() = 0;
  virtual void handleKeyPress(SDL_Event* e) = 0;
};
