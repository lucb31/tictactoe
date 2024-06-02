#pragma once
#include <engine/player/Player.hpp>

class RealPlayer : public Player {
 public:
  RealPlayer(int& playerValue) : Player{playerValue} {}
  void handleKeyPress(SDL_Event* e);
};