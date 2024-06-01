#include <SDL2/SDL.h>

class GameUI {
 private:
  // Screen dimension constants
  const int SCREEN_WIDTH = 640;
  const int SCREEN_HEIGHT = 480;

  // The window we'll be rendering to
  SDL_Window* gWindow = NULL;
  // Window renderer
  SDL_Renderer* gRenderer = NULL;
  // Window surface
  SDL_Surface* gSurface = NULL;

  bool init();

 public:
  GameUI();
  ~GameUI();
  void drawBoard();
  void drawLandingView();
  void drawGameOver();
};