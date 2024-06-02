#pragma once
#include <SDL2/SDL.h>

#include <engine/Board.hpp>
#include <gui/GameScene.hpp>
#include <gui/LTexture.hpp>
#include <gui/SceneContext.hpp>

class GameSceneBoard : public GameScene {
  LTexture fontTexture;

  Board *board;
  Uint32 myTimer = 0;

  bool init();
  bool updateActivePlayerTexture();
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
  ~GameSceneBoard();
  void render();
  void handleKeyPress(SDL_Event *e);
};
