#pragma once
#include <engine/player/Player.hpp>

class AIPlayer : public Player {
 public:
  AIPlayer(int& playerValue) : Player{playerValue} {}
  void handleKeyPress(SDL_Event* e) {}
  int getNextMove();
};