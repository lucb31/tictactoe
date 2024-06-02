#pragma once
#include <SDL2/SDL.h>

#include <gui/GameScene.hpp>

class GameSceneBoard : public GameScene {
  void drawBoard(SDL_Renderer *renderer, const int &screenWidth,
                 const int &screenHeight);

 public:
  void render(SDL_Renderer *renderer, const int &screenWidth,
              const int &screenHeight);
  void handleKeyPress(SDL_Event *e);
};
