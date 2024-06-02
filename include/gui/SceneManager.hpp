#pragma once

#include <SDL2/SDL.h>

#include <gui/GameScene.hpp>

class SceneManager {
  GameScene *activeScene = NULL;

  // Screen dimension constants
  const int screenWidth;
  const int screenHeight;

  // SDL Dependencies
  SDL_Renderer *renderer = NULL;

 public:
  SceneManager(SDL_Renderer *renderer, const int &screenWidth,
               const int &screenHeight)
      : renderer(renderer),
        screenWidth(screenWidth),
        screenHeight(screenHeight) {}
  void switchScene(GameScenes targetScene);
  void render();
  void handleKeyPress(SDL_Event *e) { activeScene->handleKeyPress(e); }
};