#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdlib.h>

#include <gui/GameScene.hpp>
#include <gui/GameUI.hpp>
#include <gui/SceneManager.hpp>

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
  gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_PRESENTVSYNC);
  if (gRenderer == NULL) {
    printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
    return false;
  }

  // Get window surface
  gSurface = SDL_GetWindowSurface(gWindow);

  // Initialize SDL_ttf
  if (TTF_Init() == -1) {
    printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
    return false;
  }

  return true;
}

bool GameUI::loadMedia() {
  // Open the font
  // Todo use relative path
  gFont = TTF_OpenFont(
      "/home/lucas/projects/tictactoe/resources/MouldyCheeseRegular.ttf", 28);
  if (gFont == NULL) {
    printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
    return false;
  }

  return true;
}

void GameUI::start() {
  // Initialize starting scene
  SceneContext context = {gRenderer, gFont, SCREEN_WIDTH, SCREEN_HEIGHT};
  sceneManager = new SceneManager(&context);
  sceneManager->switchScene(GAME_SCENE_MENU);

  SDL_Event e;
  bool quit = false;

  // Game loop: Exited if game is over OR user requests to close the GUI
  while (!quit) {
    sceneManager->render();

    // Listen for events
    if (SDL_PollEvent(&e) != 0) {
      // User requested quit
      if (e.type == SDL_QUIT) {
        quit = true;
      } else if (e.type == SDL_KEYDOWN) {
        sceneManager->handleKeyPress(&e);
      }
    }
  }
}

void GameUI::close() {
  // Free global font
  TTF_CloseFont(gFont);
  gFont = NULL;

  // Destroy window
  SDL_DestroyWindow(gWindow);
  SDL_DestroyRenderer(gRenderer);
  gWindow = NULL;
  gRenderer = NULL;

  // Quit SDL subsystems
  SDL_Quit();
  TTF_Quit();
}