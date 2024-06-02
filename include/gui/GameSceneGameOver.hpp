#pragma once
#include <gui/GameScene.hpp>
#include <gui/LTexture.hpp>

class GameSceneGameOver : public GameScene {
 private:
  LTexture fontTexture;

  bool init();

 protected:
  GameScenes currentScene = GAME_SCENE_GAME_OVER;
  void draw();
  void processFrame() {}

 public:
  GameSceneGameOver(SceneContext *sceneContext) : GameScene(sceneContext) {
    init();
  }
  ~GameSceneGameOver();
  void handleKeyPress(SDL_Event *e);
};
