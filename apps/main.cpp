#include <engine/Board.hpp>
#include <engine/player/AIPlayer.hpp>
#include <engine/player/RealPlayer.hpp>
#include <gui/GameUI.hpp>
#include <iostream>

int main(int argc, char* args[]) {
  // Setup
  srand(time(NULL));

  // Init GUI
  GameUI gui;
  gui.drawLandingView();

  // Init Game
  Board myBoard;

  // Game loop
  gui.drawBoard();
  myBoard.printState();
  while (!myBoard.isOver()) {
    myBoard.nextTurn();
  }

  // Game Over -> Wait for exit
  gui.drawGameOver();
  return 0;
}