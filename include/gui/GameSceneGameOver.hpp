#pragma once
#include <gui/GameScene.hpp>

class GameSceneGameOver : public GameScene {
 protected:
  GameScenes currentScene = GAME_SCENE_GAME_OVER;

 public:
  void render(SDL_Renderer *renderer, const int &screenWidth,
              const int &screenHeight);
  void handleKeyPress(SDL_Event *e);
};
