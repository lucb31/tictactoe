#pragma once
#include <gui/GameScene.hpp>
#include <gui/LTexture.hpp>

class GameSceneGameOver : public GameScene {
 private:
  LTexture fontTexture;

  bool init();

 protected:
  GameScenes currentScene = GAME_SCENE_GAME_OVER;

 public:
  GameSceneGameOver(SceneContext *sceneContext) : GameScene(sceneContext) {
    init();
  }
  ~GameSceneGameOver();
  void render();
  void handleKeyPress(SDL_Event *e);
};
