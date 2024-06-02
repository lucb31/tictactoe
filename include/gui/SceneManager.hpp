#pragma once

#include <gui/GameScene.hpp>
#include <gui/SceneContext.hpp>

class SceneManager {
  GameScene *activeScene = NULL;
  SceneContext *sceneContext = NULL;

 public:
  SceneManager(SceneContext *sceneContext) : sceneContext(sceneContext) {}
  void switchScene(GameScenes targetScene);
  void processFrame();
  void handleKeyPress(SDL_Event *e) { activeScene->handleKeyPress(e); }
};