#pragma once
#include <SDL2/SDL.h>

class Player {
  // Value that will be assigned to the board to represent this player
  const int playerValue;

 public:
  Player(const int& playerValue) : playerValue(playerValue) {}
  int getValue() { return playerValue; }
  virtual void setInactive() = 0;
  virtual void setActive() = 0;
  // Returns position (1-9) of next field to occupy
  virtual int getNextMove() = 0;
  virtual int getSelectedMove() = 0;
  virtual void handleKeyPress(SDL_Event* e) = 0;
};
