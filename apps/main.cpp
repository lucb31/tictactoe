#include <engine/Board.hpp>
#include <engine/player/AIPlayer.hpp>
#include <engine/player/RealPlayer.hpp>
#include <gui/GameUI.hpp>
#include <iostream>

/**
 * Known bugs
 * - Cannot close gui window while game is in progress (missing event listener)
 *
 * Next steps
 * - Draw board in GUI
 *
 */

int main(int argc, char* args[]) {
  // Setup
  srand(time(NULL));

  // Init Game state
  Board myBoard;
  myBoard.printState();

  // Init GUI
  GameUI gui(&myBoard);

  // Start game loop
  gui.start();

  // Cleanup
  gui.close();
  return 0;
}