#pragma once
#include <gui/SceneContext.hpp>

enum GameScenes {
  GAME_SCENE_UNDEF,
  GAME_SCENE_MENU,
  GAME_SCENE_BOARD,
  GAME_SCENE_GAME_OVER,
};

class GameScene {
 private:
  // Clear scene before rendering new content
  void resetScreen();

 protected:
  SceneContext *sceneContext = NULL;

  bool needsRender = true;
  GameScenes currentScene = GAME_SCENE_UNDEF;
  GameScenes nextScene = GAME_SCENE_UNDEF;

  // Abstract: Render content of current scene
  virtual void render() = 0;

 public:
  GameScene(SceneContext *sceneContext) : sceneContext(sceneContext) {}
  GameScenes getCurrentScene() { return currentScene; }
  GameScenes getNextScene() { return nextScene; }
  // Ensure scene is only re-rendered if required
  void renderFrame();
  virtual void handleKeyPress(SDL_Event *e) = 0;
};
