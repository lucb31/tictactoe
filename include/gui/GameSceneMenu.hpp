#pragma once
#include <SDL2/SDL.h>

#include <gui/GameScene.hpp>

class GameSceneMenu : public GameScene {
 protected:
  GameScenes currentScene = GAME_SCENE_MENU;

 public:
  void render(SDL_Renderer *renderer, const int &screenWidth,
              const int &screenHeight);
  void handleKeyPress(SDL_Event *e);
};
