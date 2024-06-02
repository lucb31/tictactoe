#include <SDL2/SDL.h>
#include <string.h>

#include <engine/Board.hpp>
#include <gui/GameSceneBoard.hpp>

void GameSceneBoard::processFrame() {
  // Try to execute next turn
  if (board->nextTurn()) {
    // update required if a turn was executed
    updateActivePlayerTexture();
    needsRender = true;
  }
}

bool GameSceneBoard::init() { return updateActivePlayerTexture(); }

bool GameSceneBoard::updateActivePlayerTexture() {
  Player *activePlayer = board->getActivePlayer();
  char buffer[50];
  sprintf(buffer, "Active player: Player %d", activePlayer->getValue());
  SDL_Color textColor = {0, 0, 0};
  if (!fontTexture.loadFromRenderedText(buffer, textColor, sceneContext->gFont,
                                        sceneContext->renderer)) {
    printf("Failed to render text texture!\n");
    return false;
  }
  return true;
}

void GameSceneBoard::draw() {
  drawBoard();
  // Render active player text
  fontTexture.render(sceneContext->renderer, 20, 20);
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
}

void GameSceneBoard::handleKeyPress(SDL_Event *e) {
  // Propagate event to active player
  board->getActivePlayer()->handleKeyPress(e);
  // Switch to Game over scene on space bar
  if (e->key.keysym.sym == SDLK_SPACE) {
    if (board->isOver()) {
      nextScene = GAME_SCENE_GAME_OVER;
    }
  }
}

void GameSceneBoard::drawBoardGrid() {
  const int rows = board->getHeight();
  const int cols = board->getWidth();
  const int padding = 20;
  // Set color: black
  SDL_SetRenderDrawColor(sceneContext->renderer, 0x00, 0x00, 0x00, 0xFF);
  // Render horizontal lines
  for (int i = 1; i <= rows; i++) {
    SDL_RenderDrawLine(sceneContext->renderer, padding,
                       sceneContext->screenHeight / rows * i,
                       sceneContext->screenWidth - padding,
                       sceneContext->screenHeight / rows * i);
  }
  // Render vertical lines
  for (int j = 1; j <= cols; j++) {
    SDL_RenderDrawLine(sceneContext->renderer,
                       sceneContext->screenWidth / cols * j, padding,
                       sceneContext->screenWidth / cols * j,
                       sceneContext->screenHeight - padding);
  }
}

int calcCenterX(const int &boardX, const int &boardWidth,
                const int &screenWidth) {
  return screenWidth / (boardWidth * 2) * (boardX * 2 + 1);
}

int calcCenterY(const int &boardY, const int &boardHeight,
                const int &screenHeight) {
  return screenHeight / (boardHeight * 2) * (boardY * 2 + 1);
}

int calcIconSize(const int &screenWidth, const int &screenHeight) {
  return screenWidth > screenHeight ? screenWidth / 15 : screenHeight / 15;
}

void GameSceneBoard::drawCross(const int &boardX, const int &boardY) {
  // Render cross at center pos (blue)
  SDL_SetRenderDrawColor(sceneContext->renderer, 0x00, 0x00, 0xFF, 0xFF);
  int center_x =
      calcCenterX(boardX, board->getWidth(), sceneContext->screenWidth);
  int center_y =
      calcCenterY(boardY, board->getHeight(), sceneContext->screenHeight);
  int size =
      calcIconSize(sceneContext->screenWidth, sceneContext->screenHeight);
  SDL_RenderDrawLine(sceneContext->renderer, center_x - size, center_y - size,
                     center_x + size, center_y + size);
  SDL_RenderDrawLine(sceneContext->renderer, center_x - size, center_y + size,
                     center_x + size, center_y - size);
}

void GameSceneBoard::drawRect(const int &boardX, const int &boardY) {
  // Render outlined quad (green)
  int center_x =
      calcCenterX(boardX, board->getWidth(), sceneContext->screenWidth);
  int center_y =
      calcCenterY(boardY, board->getHeight(), sceneContext->screenHeight);
  int size =
      calcIconSize(sceneContext->screenWidth, sceneContext->screenHeight);
  SDL_Rect outlineRect = {center_x - size, center_y - size, size * 2, size * 2};
  SDL_SetRenderDrawColor(sceneContext->renderer, 0x00, 0xFF, 0x00, 0xFF);
  SDL_RenderDrawRect(sceneContext->renderer, &outlineRect);
}

void GameSceneBoard::drawBoard() {
  drawBoardGrid();

  // Draw crosses & rects for board state
  int **boardState = board->getState();
  for (int x = 0; x < board->getWidth(); x++) {
    for (int y = 0; y < board->getHeight(); y++) {
      if (boardState[x][y] == 1) {
        drawCross(x, y);
      } else if (boardState[x][y] == 2) {
        drawRect(x, y);
      }
    }
  }
}

GameSceneBoard::GameSceneBoard(SceneContext *context) : GameScene(context) {
  // Init Game state
  board = new Board();

  init();
}

GameSceneBoard::~GameSceneBoard() { fontTexture.free(); }