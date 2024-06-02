#pragma once
#include <SDL2/SDL.h>

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
  // Screen dimension constants
  const int screenWidth;
  const int screenHeight;

  // SDL Dependencies
  SDL_Renderer *renderer = NULL;

  bool needsRender = true;
  GameScenes currentScene = GAME_SCENE_UNDEF;
  GameScenes nextScene = GAME_SCENE_UNDEF;

  // Abstract: Render content of current scene
  virtual void render() = 0;

 public:
  GameScene(SDL_Renderer *renderer, const int &screenWidth,
            const int &screenHeight)
      : renderer(renderer),
        screenWidth(screenWidth),
        screenHeight(screenHeight) {}
  GameScenes getCurrentScene() { return currentScene; }
  GameScenes getNextScene() { return nextScene; }
  // Ensure scene is only re-rendered if required
  void renderFrame();
  virtual void handleKeyPress(SDL_Event *e) = 0;
};
