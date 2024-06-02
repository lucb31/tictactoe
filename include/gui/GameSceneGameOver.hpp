#pragma once
#include <gui/GameScene.hpp>

class GameSceneGameOver : public GameScene {
 protected:
  GameScenes currentScene = GAME_SCENE_GAME_OVER;

 public:
  GameSceneGameOver(SDL_Renderer *renderer, const int &screenWidth,
                    const int &screenHeight)
      : GameScene(renderer, screenWidth, screenHeight) {}
  void render();
  void handleKeyPress(SDL_Event *e);
};
