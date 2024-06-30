#pragma once
#include <engine/player/Player.hpp>

class RealPlayer : public Player {
 private:
  int nextMove = -1;
  // Selected move indicates position for user selection before confirmation
  int selectedMove = -1;

 public:
  RealPlayer(int& playerValue) : Player{playerValue} {}
  void setInactive() { selectedMove = -1; }
  void setActive() { selectedMove = 5; }

  // Listen to key events to queue up next move
  void handleKeyPress(SDL_Event* e);
  // Return queued up move
  int getNextMove();
  int getSelectedMove() { return selectedMove; }
};