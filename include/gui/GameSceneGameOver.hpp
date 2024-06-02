#pragma once
#include <gui/GameScene.hpp>

class GameSceneGameOver : public GameScene {
 protected:
  GameScenes currentScene = GAME_SCENE_GAME_OVER;

 public:
  GameSceneGameOver(SceneContext *sceneContext) : GameScene(sceneContext) {}
  ~GameSceneGameOver();
  void render();
  void handleKeyPress(SDL_Event *e);
};
