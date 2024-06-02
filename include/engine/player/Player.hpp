#pragma once
#include <SDL2/SDL.h>

class Player {
  // Value that will be assigned to the board to represent this player
  const int playerValue;

 protected:
  int nextMove = -1;

 public:
  Player(const int& playerValue) : playerValue(playerValue) {}
  // Returns position (1-9) of next field to occupy
  int getNextMove() { return nextMove; }
  void resetNextMove() { nextMove = -1; }
  int getValue() { return playerValue; }
  virtual void handleKeyPress(SDL_Event* e) = 0;
};
