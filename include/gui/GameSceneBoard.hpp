#pragma once
#include <SDL2/SDL.h>

#include <engine/Board.hpp>
#include <gui/GameScene.hpp>

class GameSceneBoard : public GameScene {
  Board *board;
  Uint32 myTimer = 0;
  void drawBoard(SDL_Renderer *renderer, const int &screenWidth,
                 const int &screenHeight);

 protected:
  GameScenes currentScene = GAME_SCENE_BOARD;

 public:
  GameSceneBoard();
  void render(SDL_Renderer *renderer, const int &screenWidth,
              const int &screenHeight);
  void handleKeyPress(SDL_Event *e);
};
