#pragma once

#include <gui/GameScene.hpp>

class SceneManager {
  GameScene *activeScene = NULL;

 public:
  void switchScene(GameScenes targetScene);
  void render(SDL_Renderer *renderer, const int &screenWidth,
              const int &screenHeight);
  void handleKeyPress(SDL_Event *e) { activeScene->handleKeyPress(e); }
};