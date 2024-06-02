#include <SDL2/SDL.h>

#include <gui/GameSceneGameOver.hpp>

void GameSceneGameOver::render(SDL_Renderer *renderer, const int &screenWidth,
                               const int &screenHeight) {
  // Render red outlined quad
  SDL_Rect outlineRect = {screenWidth / 6, screenHeight / 6,
                          screenWidth * 2 / 3, screenHeight * 2 / 3};
  SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
  SDL_RenderDrawRect(renderer, &outlineRect);
  // Update screen
  SDL_RenderPresent(renderer);
}

void GameSceneGameOver::handleKeyPress(SDL_Event *e) {
  // Switch to MENU scene on space bar
  if (e->key.keysym.sym == SDLK_SPACE) {
    nextScene = GAME_SCENE_MENU;
  }
}