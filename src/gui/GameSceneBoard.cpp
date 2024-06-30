#include <SDL2/SDL.h>
#include <string.h>

#include <engine/Board.hpp>
#include <gui/GameSceneBoard.hpp>

#define PI 3.141592654

void GameSceneBoard::processFrame() {
  if (board->isOver()) {
    // Switch to Game over scene
    nextScene = GAME_SCENE_GAME_OVER;
    return;
  }
  // Try to execute next turn
  if (board->nextTurn()) {
    // update required if a turn was executed
    updateActivePlayerTexture();
  }
}

bool GameSceneBoard::init() {
  iconSize =
      calcIconSize(sceneContext->screenWidth, sceneContext->screenHeight);
  // Init Game state
  board = new Board();

  // Init active player texture
  if (!updateActivePlayerTexture()) {
    return false;
  }

  // Init preview textures
  for (int i = 0; i < 9; i++) {
    SDL_Color textColor = {0, 0, 0};
    char buffer[2];
    sprintf(buffer, "%d", i + 1);
    if (!previewTextures[i].loadFromRenderedText(
            buffer, textColor, sceneContext->gFont, sceneContext->renderer)) {
      printf("Failed to render preview texture!\n");
      return false;
    }
  }
  return true;
}

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
}

void GameSceneBoard::handleKeyPress(SDL_Event *e) {
  // Propagate event to active player
  board->getActivePlayer()->handleKeyPress(e);
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

// Ensures size of icons scales with screen dimension
int calcIconSize(const int &screenWidth, const int &screenHeight) {
  return screenWidth > screenHeight ? screenWidth / 25 : screenHeight / 25;
}

// Render cross at center pos
void GameSceneBoard::drawCross(const int &boardX, const int &boardY) {
  // Transform board position into screen position
  int center_x =
      calcCenterX(boardX, board->getWidth(), sceneContext->screenWidth);
  int center_y =
      calcCenterY(boardY, board->getHeight(), sceneContext->screenHeight);

  double rotationAngle = 0 + totalFrames * 0.5f;
  double radians = (rotationAngle * PI) / 180;

  // Set blue render color
  SDL_SetRenderDrawColor(sceneContext->renderer, 0x00, 0x00, 0xFF, 0xFF);
  // First line
  int end_x = cos(radians) * iconSize;
  int end_y = sin(radians) * iconSize;
  SDL_RenderDrawLine(sceneContext->renderer, center_x + end_x, center_y + end_y,
                     center_x - end_x, center_y - end_y);
  // Second line rotated by 90°
  int end_x_2 = cos(radians + PI / 2) * iconSize;
  int end_y_2 = sin(radians + PI / 2) * iconSize;
  SDL_RenderDrawLine(sceneContext->renderer, center_x + end_x_2,
                     center_y + end_y_2, center_x - end_x_2,
                     center_y - end_y_2);
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
      } else {
        // render preview texture
        int idx = y * board->getHeight() + x;
        previewTextures[idx].render(
            sceneContext->renderer,
            calcCenterX(x, board->getWidth(), sceneContext->screenWidth),
            calcCenterY(y, board->getHeight(), sceneContext->screenHeight));
      }
    }
  }
}

GameSceneBoard::~GameSceneBoard() {
  fontTexture.free();
  previewTextures->free();
}