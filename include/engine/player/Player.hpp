#pragma once

class Player {
  // Value that will be assigned to the board to represent this player
  int playerValue;

 public:
  Player(int& playerValue) : playerValue(playerValue) {}
  virtual int getNextMove() = 0;
  int getValue() { return playerValue; }
};
