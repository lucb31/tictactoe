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

void GameUI::drawLandingView() {
  // Reset screen
  SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
  SDL_RenderClear(gRenderer);
  // Render green outlined quad
  SDL_Rect outlineRect = {SCREEN_WIDTH / 6, SCREEN_HEIGHT / 6,
                          SCREEN_WIDTH * 2 / 3, SCREEN_HEIGHT * 2 / 3};
  SDL_SetRenderDrawColor(gRenderer, 0x00, 0xFF, 0x00, 0xFF);
  SDL_RenderDrawRect(gRenderer, &outlineRect);

  SDL_RenderPresent(gRenderer);
}

void GameUI::drawBoard() {
  // Reset screen
  SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
  SDL_RenderClear(gRenderer);
  // Render red filled quad
  SDL_Rect fillRect = {SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4, SCREEN_WIDTH / 2,
                       SCREEN_HEIGHT / 2};
  SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0x00, 0xFF);
  SDL_RenderFillRect(gRenderer, &fillRect);
  // Render green outlined quad
  SDL_Rect outlineRect = {SCREEN_WIDTH / 6, SCREEN_HEIGHT / 6,
                          SCREEN_WIDTH * 2 / 3, SCREEN_HEIGHT * 2 / 3};
  SDL_SetRenderDrawColor(gRenderer, 0x00, 0xFF, 0x00, 0xFF);
  SDL_RenderDrawRect(gRenderer, &outlineRect);
  // Render blue horizontal line
  SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0xFF, 0xFF);
  SDL_RenderDrawLine(gRenderer, 0, SCREEN_HEIGHT / 2, SCREEN_WIDTH,
                     SCREEN_HEIGHT / 2);
  // Render vert line of yellow dots
  SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0x00, 0xFF);
  for (int i = 0; i < 10; i++) {
    SDL_RenderDrawPoint(gRenderer, SCREEN_WIDTH / 2, i);
  }

  SDL_RenderPresent(gRenderer);
}

void GameUI::drawGameOver() {
  printf("Game Over! Waiting for confirmation to close window\n");

  // Reset screen
  SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0xFF, 0xFF);
  SDL_RenderClear(gRenderer);
  // Render green outlined quad
  SDL_Rect outlineRect = {SCREEN_WIDTH / 6, SCREEN_HEIGHT / 6,
                          SCREEN_WIDTH * 2 / 3, SCREEN_HEIGHT * 2 / 3};
  SDL_SetRenderDrawColor(gRenderer, 0x00, 0xFF, 0x00, 0xFF);
  SDL_RenderDrawRect(gRenderer, &outlineRect);
  // Update screen
  SDL_RenderPresent(gRenderer);

  // Wait for user confirmation to close window
  bool quit = false;
  SDL_Event e;
  while (!quit) {
    while (SDL_PollEvent(&e) != 0) {
      // User requested quit
      if (e.type == SDL_QUIT) {
        quit = true;
      }
    }
  }
}

GameUI::GameUI() { init(); }

GameUI::~GameUI() {
  // Destroy window
  SDL_DestroyWindow(gWindow);
  SDL_DestroyRenderer(gRenderer);
  gWindow = NULL;
  gRenderer = NULL;

  // Quit SDL subsystems
  SDL_Quit();
}