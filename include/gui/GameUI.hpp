#pragma once
#include <SDL2/SDL.h>

#include <engine/Board.hpp>
#include <gui/SceneManager.hpp>

class GameUI {
 private:
  // Screen dimension constants
  const int SCREEN_WIDTH = 640;
  const int SCREEN_HEIGHT = 480;

  // SDL Dependencies
  SDL_Window* gWindow = NULL;
  SDL_Renderer* gRenderer = NULL;
  SDL_Surface* gSurface = NULL;

  // Scene management
  SceneManager* sceneManager = NULL;
  // Todo Move to board scene
  Board* board;
  Uint32 myTimer = 0;

  bool init();

 public:
  // Todo remove board
  GameUI(Board* board) : board(board) { init(); }
  // Starts the main game loop
  void start();
  void close();
};