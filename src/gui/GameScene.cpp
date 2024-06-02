#include <SDL2/SDL.h>

#include <gui/GameScene.hpp>
#include <iostream>

void GameScene::renderFrame(SDL_Renderer *renderer, const int &screenWidth,
                            const int &screenHeight) {
  // Ensures scene is only rendered if content has changed
  if (!needsRender) {
    return;
  }

  std::cout << "Scene needs to be re-rendered\n";
  // Reset screen before drawing new content
  resetScreen(renderer, screenWidth, screenHeight);
  render(renderer, screenWidth, screenHeight);
  needsRender = false;
}

void GameScene::resetScreen(SDL_Renderer *renderer, const int &screenWidth,
                            const int &screenHeight) {
  SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
  SDL_RenderClear(renderer);
}