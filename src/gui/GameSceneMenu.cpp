#include <SDL2/SDL.h>
#include <stdlib.h>

#include <gui/GameSceneGameOver.hpp>
#include <gui/GameSceneMenu.hpp>
#include <iostream>

void GameSceneMenu::render() {
  // Render green outlined quad
  SDL_Rect outlineRect = {screenWidth / 6, screenHeight / 6,
                          screenWidth * 2 / 3, screenHeight * 2 / 3};
  SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0x00, 0xFF);
  SDL_RenderDrawRect(renderer, &outlineRect);

  SDL_RenderPresent(renderer);
}

void GameSceneMenu::handleKeyPress(SDL_Event *e) {
  // Switch to Board scene on space bar
  if (e->key.keysym.sym == SDLK_SPACE) {
    nextScene = GAME_SCENE_BOARD;
  }
}