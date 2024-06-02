#include <SDL2/SDL.h>
#include <stdlib.h>

#include <gui/GameSceneGameOver.hpp>
#include <gui/GameSceneMenu.hpp>
#include <iostream>

bool GameSceneMenu::init() {
  // Render text
  SDL_Color textColor = {0, 0, 0};
  if (!fontTexture.loadFromRenderedText("Tic tac toe", textColor,
                                        sceneContext->gFont,
                                        sceneContext->renderer)) {
    printf("Failed to render text texture!\n");
    return false;
  }
  return true;
}
void GameSceneMenu::render() {
  // Render green outlined quad
  SDL_Rect outlineRect = {
      sceneContext->screenWidth / 6, sceneContext->screenHeight / 6,
      sceneContext->screenWidth * 2 / 3, sceneContext->screenHeight * 2 / 3};
  SDL_SetRenderDrawColor(sceneContext->renderer, 0x00, 0xFF, 0x00, 0xFF);
  SDL_RenderDrawRect(sceneContext->renderer, &outlineRect);

  // Render text
  fontTexture.render(
      sceneContext->renderer,
      (sceneContext->screenWidth - fontTexture.getWidth()) / 2,
      (sceneContext->screenHeight - fontTexture.getHeight()) / 2);
}

GameSceneMenu::~GameSceneMenu() { fontTexture.free(); }

void GameSceneMenu::handleKeyPress(SDL_Event *e) {
  // Switch to Board scene on space bar
  if (e->key.keysym.sym == SDLK_SPACE) {
    nextScene = GAME_SCENE_BOARD;
  }
}