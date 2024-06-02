#include <SDL2/SDL.h>

#include <gui/GameSceneGameOver.hpp>

bool GameSceneGameOver::init() {
  // Render text
  SDL_Color textColor = {255, 0, 0};
  if (!fontTexture.loadFromRenderedText(
          "GameOver", textColor, sceneContext->gFont, sceneContext->renderer)) {
    printf("Failed to render text texture!\n");
    return false;
  }
  return true;
}
void GameSceneGameOver::draw() {
  // Render red outlined quad
  SDL_Rect outlineRect = {
      sceneContext->screenWidth / 6, sceneContext->screenHeight / 6,
      sceneContext->screenWidth * 2 / 3, sceneContext->screenHeight * 2 / 3};
  SDL_SetRenderDrawColor(sceneContext->renderer, 0xFF, 0x00, 0x00, 0xFF);
  SDL_RenderDrawRect(sceneContext->renderer, &outlineRect);

  // Render game over text
  fontTexture.render(
      sceneContext->renderer,
      (sceneContext->screenWidth - fontTexture.getWidth()) / 2,
      (sceneContext->screenHeight - fontTexture.getHeight()) / 2);
}

GameSceneGameOver::~GameSceneGameOver() { fontTexture.free(); }

void GameSceneGameOver::handleKeyPress(SDL_Event *e) {
  // Switch to MENU scene on space bar
  if (e->key.keysym.sym == SDLK_SPACE) {
    nextScene = GAME_SCENE_MENU;
  }
}