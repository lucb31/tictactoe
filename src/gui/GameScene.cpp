#include <SDL2/SDL.h>

#include <gui/GameScene.hpp>
#include <iostream>
#include <sstream>

void GameScene::render() {
  fpsCapTimer.start();
  // Proceed scene logic by one frame
  processFrame();

  // Reset screen before drawing new content
  resetScreen();
  renderFrameRate();
  draw();
  // Update screen
  SDL_RenderPresent(sceneContext->renderer);
  int frameTicks = fpsCapTimer.getTicks();
  if (frameTicks < SCREEN_TICKS_PER_FRAME) {
    SDL_Delay(SCREEN_TICKS_PER_FRAME - frameTicks);
  }
}

void GameScene::renderFrameRate() {
  // Calculate & limit avg fps
  float avgFps = totalFrames / (fpsTimer.getTicks() / 1000.0f);
  if (avgFps > 200000) {
    avgFps = 0;
  }

  // Assemble texture
  std::stringstream timeText;
  timeText.str();
  timeText << "FPS " << avgFps;
  SDL_Color textColor = {255, 0, 0};
  if (!fpsTexture.loadFromRenderedText(timeText.str().c_str(), textColor,
                                       sceneContext->gFont,
                                       sceneContext->renderer)) {
    printf("Failed to render fps texture!\n");
    return;
  }

  // Render
  fpsTexture.render(sceneContext->renderer,
                    sceneContext->screenWidth - fpsTexture.getWidth() - 50, 20);

  // Increase fps counter
  totalFrames++;
}

void GameScene::resetScreen() {
  SDL_SetRenderDrawColor(sceneContext->renderer, 0xFF, 0xFF, 0xFF, 0xFF);
  SDL_RenderClear(sceneContext->renderer);
}

GameScene::GameScene(SceneContext *sceneContext) : sceneContext(sceneContext) {
  fpsTimer.start();
}