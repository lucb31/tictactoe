#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

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
  TTF_Font* gFont = NULL;

  // Scene management
  SceneManager* sceneManager = NULL;

  bool init();
  bool loadMedia();

 public:
  GameUI() {
    init();
    loadMedia();
  }
  // Starts the main game loop
  void start();
  void close();
};