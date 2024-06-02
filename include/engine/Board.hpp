#pragma once
#include <engine/player/Player.hpp>
#include <tuple>

class Board {
  const int N_ROWS = 3;
  const int N_COLS = 3;
  /*
  0 = Unset
  1 = Player 1
  2 = Player 2
  */
  int **gameState;
  int currentTurn = 0;
  Player *player1;
  Player *player2;

  int getWinner();

  bool hasVacantFields();

  std::tuple<int, int> posToXY(int const &position);

  int posFromXY(int const &x, int const &y);

  void initializeMap();

  void initializePlayers();

 public:
  Board();

  Player *getActivePlayer();
  int **getState() { return gameState; }

  // Returns true if turn was executed
  bool nextTurn();

  const int getField(int const &position);
  void setField(int const &position, int const &playerIndex);

  bool isOver();

  const int &getWidth() { return N_COLS; }
  const int &getHeight() { return N_ROWS; }
};