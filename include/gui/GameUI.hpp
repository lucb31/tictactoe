#include <SDL2/SDL.h>

#include <engine/Board.hpp>

enum GameScene {
  GAME_SCENE_START,
  GAME_SCENE_BOARD,
  GAME_SCENE_GAME_OVER,
};

class GameUI {
 private:
  // Screen dimension constants
  const int SCREEN_WIDTH = 640;
  const int SCREEN_HEIGHT = 480;

  GameScene activeScene = GAME_SCENE_START;
  Board* board;

  // SDL Dependencies
  SDL_Window* gWindow = NULL;
  SDL_Renderer* gRenderer = NULL;
  SDL_Surface* gSurface = NULL;
  bool needsRender = true;

  bool init();
  void render();
  void resetScreen();
  void switchScene(GameScene targetScene);
  void drawBoard();
  void drawLandingView();
  void drawGameOver();

 public:
  GameUI(Board* board) : board(board) { init(); };
  // Starts the main game loop
  void start();
  void close();
};