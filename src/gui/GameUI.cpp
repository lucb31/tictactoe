#include <SDL2/SDL.h>

#include <gui/GameUI.hpp>

bool GameUI::init() {
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    return false;
  }
  // Create window
  gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED,
                             SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                             SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
  if (gWindow == NULL) {
    printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
    return false;
  }
  // Create renderer
  gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
  if (gRenderer == NULL) {
    printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
    return false;
  }

  // Get window surface
  gSurface = SDL_GetWindowSurface(gWindow);

  return true;
}

void GameUI::start() {
  SDL_Event e;
  bool quit = false;
  // Game loop: Exited if game is over OR user requests to close the GUI
  while (!quit) {
    render();
    // !board->isOver() &&
    // myBoard.nextTurn();

    // Listen for events
    if (SDL_PollEvent(&e) != 0) {
      // User requested quit
      if (e.type == SDL_QUIT) {
        quit = true;
      }
      // Switch to Board scene on space bar
      else if (e.type == SDL_KEYDOWN) {
        if (e.key.keysym.sym == SDLK_SPACE) {
          switchScene(GAME_SCENE_BOARD);
        }
      }
    }
    // Switch scene to game over if board state is over
    if (board->isOver()) {
      activeScene = GAME_SCENE_GAME_OVER;
    }
  }
}

void GameUI::switchScene(GameScene targetScene) {
  activeScene = targetScene;
  needsRender = true;
}

void GameUI::render() {
  // Only re-render if board state has changed
  if (!needsRender) {
    return;
  }
  printf("Re-rendering scene %d \n", activeScene);
  switch (activeScene) {
    case GAME_SCENE_START:
      drawLandingView();
      break;
    case GAME_SCENE_BOARD:
      drawBoard();
      break;
    default:
      drawGameOver();
      break;
  }
  needsRender = false;
}

void GameUI::resetScreen() {
  SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
  SDL_RenderClear(gRenderer);
}

void GameUI::drawLandingView() {
  resetScreen();
  // Render green outlined quad
  SDL_Rect outlineRect = {SCREEN_WIDTH / 6, SCREEN_HEIGHT / 6,
                          SCREEN_WIDTH * 2 / 3, SCREEN_HEIGHT * 2 / 3};
  SDL_SetRenderDrawColor(gRenderer, 0x00, 0xFF, 0x00, 0xFF);
  SDL_RenderDrawRect(gRenderer, &outlineRect);

  SDL_RenderPresent(gRenderer);
}

// Todo Add input parameter with board state
void GameUI::drawBoard() {
  const int rows = 3;
  const int cols = 3;
  const int padding = 40;
  printf("Rendering board");

  resetScreen();
  // Render grid
  // Render horizontal lines (black)
  SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
  for (int i = 1; i <= rows; i++) {
    SDL_RenderDrawLine(gRenderer, padding, SCREEN_HEIGHT / rows * i,
                       SCREEN_WIDTH - padding, SCREEN_HEIGHT / rows * i);
  }
  // Render vertical lines
  for (int j = 1; j <= cols; j++) {
    SDL_RenderDrawLine(gRenderer, SCREEN_WIDTH / cols * j, 0,
                       SCREEN_WIDTH / cols * j, SCREEN_HEIGHT);
  }

  // Render cross at center pos (blue)
  SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0xFF, 0xFF);
  int center_x = SCREEN_WIDTH / 6 * 1;
  int center_y = SCREEN_HEIGHT / 6 * 1;
  int offset = 40;
  SDL_RenderDrawLine(gRenderer, center_x - offset, center_y - offset,
                     center_x + offset, center_y + offset);
  SDL_RenderDrawLine(gRenderer, center_x - offset, center_y + offset,
                     center_x + offset, center_y - offset);

  // Render outlined quad (green)
  center_x = SCREEN_WIDTH / 6 * 3;
  center_y = SCREEN_HEIGHT / 6 * 3;
  SDL_Rect outlineRect = {center_x - offset, center_y - offset, offset * 2,
                          offset * 2};
  SDL_SetRenderDrawColor(gRenderer, 0x00, 0xFF, 0x00, 0xFF);
  SDL_RenderDrawRect(gRenderer, &outlineRect);

  SDL_RenderPresent(gRenderer);
}

void GameUI::drawGameOver() {
  printf("Game Over! Waiting for confirmation to close window\n");

  resetScreen();
  // Render green outlined quad
  SDL_Rect outlineRect = {SCREEN_WIDTH / 6, SCREEN_HEIGHT / 6,
                          SCREEN_WIDTH * 2 / 3, SCREEN_HEIGHT * 2 / 3};
  SDL_SetRenderDrawColor(gRenderer, 0x00, 0xFF, 0x00, 0xFF);
  SDL_RenderDrawRect(gRenderer, &outlineRect);
  // Update screen
  SDL_RenderPresent(gRenderer);
}

void GameUI::close() {
  // Destroy window
  SDL_DestroyWindow(gWindow);
  SDL_DestroyRenderer(gRenderer);
  gWindow = NULL;
  gRenderer = NULL;

  // Quit SDL subsystems
  SDL_Quit();
}