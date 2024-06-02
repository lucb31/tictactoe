#pragma once
#include <SDL2/SDL.h>

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

  bool init();

 public:
  GameUI() { init(); }
  // Starts the main game loop
  void start();
  void close();
};