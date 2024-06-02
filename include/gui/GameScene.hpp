#pragma once

enum GameScenes {
  GAME_SCENE_UNDEF,
  GAME_SCENE_MENU,
  GAME_SCENE_BOARD,
  GAME_SCENE_GAME_OVER,
};

class GameScene {
 private:
  // Clear scene before rendering new content
  void resetScreen(SDL_Renderer *renderer, const int &screenWidth,
                   const int &screenHeight);

 protected:
  bool needsRender = true;
  GameScenes currentScene = GAME_SCENE_UNDEF;
  GameScenes nextScene = GAME_SCENE_UNDEF;

  // Abstract: Render content of current scene
  virtual void render(SDL_Renderer *renderer, const int &screenWidth,
                      const int &screenHeight) = 0;

 public:
  GameScenes getCurrentScene() { return currentScene; }
  GameScenes getNextScene() { return nextScene; }
  // Ensure scene is only re-rendered if required
  void renderFrame(SDL_Renderer *renderer, const int &screenWidth,
                   const int &screenHeight);
  virtual void handleKeyPress(SDL_Event *e) = 0;
};
