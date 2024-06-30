#pragma once
#include <SDL2/SDL.h>

#include <engine/Board.hpp>
#include <gui/GameScene.hpp>
#include <gui/LTexture.hpp>
#include <gui/SceneContext.hpp>

class GameSceneBoard : public GameScene {
  LTexture fontTexture;
  LTexture previewTextures[9];

  Board *board;
  int iconSize = 5;

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
  void processFrame();
  void draw();

 public:
  GameSceneBoard(SceneContext *sceneContext) : GameScene(sceneContext) {
    init();
  }
  ~GameSceneBoard();
  void handleKeyPress(SDL_Event *e);
};
