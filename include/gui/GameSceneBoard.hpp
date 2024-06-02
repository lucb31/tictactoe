#pragma once
#include <SDL2/SDL.h>

#include <engine/Board.hpp>
#include <gui/GameScene.hpp>
#include <gui/SceneContext.hpp>

class GameSceneBoard : public GameScene {
  Board *board;
  Uint32 myTimer = 0;

  // Draw the whole board scene
  void drawBoard();
  // Draw an empty grid
  void drawBoardGrid();
  void drawCross(const int &boardX, const int &boardY);
  void drawRect(const int &boardX, const int &boardY);

 protected:
  GameScenes currentScene = GAME_SCENE_BOARD;

 public:
  GameSceneBoard(SceneContext *sceneContext);
  void render();
  void handleKeyPress(SDL_Event *e);
};
