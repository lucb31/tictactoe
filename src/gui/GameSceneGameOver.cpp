#include <SDL2/SDL.h>

#include <gui/GameSceneGameOver.hpp>

void GameSceneGameOver::render() {
  // Render red outlined quad
  SDL_Rect outlineRect = {
      sceneContext->screenWidth / 6, sceneContext->screenHeight / 6,
      sceneContext->screenWidth * 2 / 3, sceneContext->screenHeight * 2 / 3};
  SDL_SetRenderDrawColor(sceneContext->renderer, 0xFF, 0x00, 0x00, 0xFF);
  SDL_RenderDrawRect(sceneContext->renderer, &outlineRect);
}

GameSceneGameOver::~GameSceneGameOver() {}

void GameSceneGameOver::handleKeyPress(SDL_Event *e) {
  // Switch to MENU scene on space bar
  if (e->key.keysym.sym == SDLK_SPACE) {
    nextScene = GAME_SCENE_MENU;
  }
}