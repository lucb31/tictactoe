#pragma once
#include <gui/LTexture.hpp>
#include <gui/LTimer.hpp>
#include <gui/SceneContext.hpp>

enum GameScenes {
  GAME_SCENE_UNDEF,
  GAME_SCENE_MENU,
  GAME_SCENE_BOARD,
  GAME_SCENE_GAME_OVER,
};

class GameScene {
 private:
  const int SCREEN_FPS = 60;
  const int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;

  // FPS Counter
  int totalFrames = 0;
  LTimer fpsTimer;
  LTimer fpsCapTimer;
  LTexture fpsTexture;

  // Clear scene before rendering new content
  void resetScreen();
  void renderFrameRate();

 protected:
  SceneContext *sceneContext = NULL;

  GameScenes currentScene = GAME_SCENE_UNDEF;
  GameScenes nextScene = GAME_SCENE_UNDEF;

  // Abstract: Draw content of current scene
  virtual void draw() = 0;
  // Contains frame logic
  virtual void processFrame() = 0;

 public:
  GameScene(SceneContext *sceneContext);
  GameScenes getCurrentScene() { return currentScene; }
  GameScenes getNextScene() { return nextScene; }
  // Ensures scene is only re-rendered if required
  void render();
  virtual void handleKeyPress(SDL_Event *e) = 0;
};
