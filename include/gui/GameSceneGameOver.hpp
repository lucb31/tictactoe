#pragma once
#include <gui/GameScene.hpp>

class GameSceneGameOver : public GameScene {
 public:
  void render(SDL_Renderer *renderer, const int &screenWidth,
              const int &screenHeight);
  void handleKeyPress(SDL_Event *e);
};
