#pragma once
#include <engine/player/Player.hpp>

class RealPlayer : public Player {
 private:
  int nextMove = -1;

 public:
  RealPlayer(int& playerValue) : Player{playerValue} {}
  // Listen to key events to queue up next move
  void handleKeyPress(SDL_Event* e);
  // Return queued up move
  int getNextMove();
};