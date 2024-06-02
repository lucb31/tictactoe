#pragma once
#include <SDL2/SDL.h>

#include <gui/GameScene.hpp>

class GameSceneBoard : public GameScene {
  void drawBoard(SDL_Renderer *renderer, const int &screenWidth,
                 const int &screenHeight);

 protected:
  GameScenes currentScene = GAME_SCENE_BOARD;

 public:
  void render(SDL_Renderer *renderer, const int &screenWidth,
              const int &screenHeight);
  void handleKeyPress(SDL_Event *e);
};
