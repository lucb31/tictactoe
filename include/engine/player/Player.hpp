#pragma once

class Player {
  // Value that will be assigned to the board to represent this player
  int playerValue;

 public:
  Player(int& playerValue) : playerValue(playerValue) {}
  // Returns position (1-9) of next field to occupy
  virtual int getNextMove() = 0;
  int getValue() { return playerValue; }
};
