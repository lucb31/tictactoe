#include <SDL2/SDL.h>

#include <engine/Board.hpp>
#include <gui/GameSceneBoard.hpp>

void GameSceneBoard::render(SDL_Renderer *renderer, const int &screenWidth,
                            const int &screenHeight) {
  drawBoard(renderer, screenWidth, screenHeight);
  // Next board turn (AI vs AI) every 2s
  // Update timer
  // Uint32 currentTime = SDL_GetTicks();
  // const int timeOffset = 2000;
  // if (currentTime > myTimer + timeOffset) {
  //   printf("Enough time has passed, executing next turn \n");
  //   board->nextTurn();
  //   needsRender = true;
  //   myTimer = currentTime;
  // }
  // // Switch scene to game over if board state is over
  // if (board->isOver()) {

  //   switchScene(GAME_SCENE_GAME_OVER);
  // }
}

void GameSceneBoard::handleKeyPress(SDL_Event *e) {
  // Switch to Game over scene on space bar
  if (e->key.keysym.sym == SDLK_SPACE) {
    if (!board->isOver()) {
      board->nextTurn();
    } else {
      nextScene = GAME_SCENE_GAME_OVER;
    }
  }
}

// Todo Draw actual board state
void GameSceneBoard::drawBoard(SDL_Renderer *renderer, const int &screenWidth,
                               const int &screenHeight) {
  const int rows = 3;
  const int cols = 3;
  const int padding = 40;

  // Render grid
  // Render horizontal lines (black)
  SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
  for (int i = 1; i <= rows; i++) {
    SDL_RenderDrawLine(renderer, padding, screenHeight / rows * i,
                       screenWidth - padding, screenHeight / rows * i);
  }
  // Render vertical lines
  for (int j = 1; j <= cols; j++) {
    SDL_RenderDrawLine(renderer, screenWidth / cols * j, 0,
                       screenWidth / cols * j, screenHeight);
  }

  // Render cross at center pos (blue)
  SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0xFF, 0xFF);
  int center_x = screenWidth / 6 * 1;
  int center_y = screenHeight / 6 * 1;
  int offset = 40;
  SDL_RenderDrawLine(renderer, center_x - offset, center_y - offset,
                     center_x + offset, center_y + offset);
  SDL_RenderDrawLine(renderer, center_x - offset, center_y + offset,
                     center_x + offset, center_y - offset);

  // Render outlined quad (green)
  center_x = screenWidth / 6 * 3;
  center_y = screenHeight / 6 * 3;
  SDL_Rect outlineRect = {center_x - offset, center_y - offset, offset * 2,
                          offset * 2};
  SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0x00, 0xFF);
  SDL_RenderDrawRect(renderer, &outlineRect);

  SDL_RenderPresent(renderer);
}

GameSceneBoard::GameSceneBoard() {
  // Init Game state
  board = new Board();
  board->printState();
}