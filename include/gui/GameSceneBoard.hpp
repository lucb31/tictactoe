#pragma once
#include <SDL2/SDL.h>

#include <engine/Board.hpp>
#include <gui/GameScene.hpp>

class GameSceneBoard : public GameScene {
  Board *board;
  Uint32 myTimer = 0;
  // Draw the whole board scene
  void drawBoard();
  // Draw an empty grid
  void drawBoardGrid();

 protected:
  GameScenes currentScene = GAME_SCENE_BOARD;

 public:
  GameSceneBoard(SDL_Renderer *renderer, const int &screenWidth,
                 const int &screenHeight);
  void render();
  void handleKeyPress(SDL_Event *e);
};
