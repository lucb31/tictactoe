#pragma once
#include <SDL2/SDL.h>

#include <gui/GameScene.hpp>

class GameSceneMenu : public GameScene {
 protected:
  GameScenes currentScene = GAME_SCENE_MENU;

 public:
  GameSceneMenu(SDL_Renderer *renderer, const int &screenWidth,
                const int &screenHeight)
      : GameScene(renderer, screenWidth, screenHeight) {}
  void render();
  void handleKeyPress(SDL_Event *e);
};
