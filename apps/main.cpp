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

  // Start game loop
  gui.start();

  // Cleanup
  gui.close();
  return 0;
}