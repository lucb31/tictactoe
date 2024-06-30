#include <SDL2/SDL.h>
#include <string.h>

#include <engine/Board.hpp>
#include <gui/GameSceneBoard.hpp>

#define PI 3.141592654

double toRad(const double &angle) { return (angle * PI) / 180; }

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
  // Scale size of icons scales with screen dimension
  iconSize = sceneContext->screenWidth > sceneContext->screenHeight
                 ? sceneContext->screenWidth / 25
                 : sceneContext->screenHeight / 25;
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
  drawBoardGrid();
  drawBoardState();
  // Render player selection preview
  Player *activePlayer = board->getActivePlayer();
  if (activePlayer->getValue() == 1) {
    int selectedMove = activePlayer->getSelectedMove();
    auto [x, y] = board->posToXY(selectedMove);
    Position myPos = {x, y};
    drawCross(myPos, true);
  }
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

Position GameSceneBoard::boardPositionToScreenPosition(
    Position &boardPosition) {
  int centerX = sceneContext->screenWidth / (board->getWidth() * 2) *
                (boardPosition.x * 2 + 1);
  int centerY = sceneContext->screenHeight / (board->getHeight() * 2) *
                (boardPosition.y * 2 + 1);
  return {centerX, centerY};
}

// Render cross at center pos
void GameSceneBoard::drawCross(Position &boardPosition, bool animated = false) {
  // Transform board position into screen position
  Position pos = boardPositionToScreenPosition(boardPosition);

  double rotationAngle = 0;
  if (animated) {
    rotationAngle += totalFrames * 0.5f;
  }

  // Set blue render color
  SDL_SetRenderDrawColor(sceneContext->renderer, 0x00, 0x00, 0xFF, 0xFF);
  // First line
  int end_x = cos(toRad(rotationAngle)) * iconSize;
  int end_y = sin(toRad(rotationAngle)) * iconSize;
  SDL_RenderDrawLine(sceneContext->renderer, pos.x + end_x, pos.y + end_y,
                     pos.x - end_x, pos.y - end_y);
  // Second line rotated by 90°
  int end_x_2 = cos(toRad(rotationAngle + 90)) * iconSize;
  int end_y_2 = sin(toRad(rotationAngle + 90)) * iconSize;
  SDL_RenderDrawLine(sceneContext->renderer, pos.x + end_x_2, pos.y + end_y_2,
                     pos.x - end_x_2, pos.y - end_y_2);
}

// Render outlined quad
void GameSceneBoard::drawRect(Position &boardPosition, bool animated = false) {
  // Transform board position into screen position
  Position pos = boardPositionToScreenPosition(boardPosition);

  double rotationAngle = 45;
  if (animated) {
    rotationAngle += totalFrames * 0.5f;
  }
  // Calculate points
  int nrPoints = 5;
  SDL_Point points[nrPoints];
  for (int i = 0; i < nrPoints; i++) {
    points[i] = {pos.x + (int)(cos(toRad(rotationAngle + 90 * i)) * iconSize),
                 pos.y + (int)(sin(toRad(rotationAngle + 90 * i)) * iconSize)};
  }

  // Set green render color
  SDL_SetRenderDrawColor(sceneContext->renderer, 0x00, 0xFF, 0x00, 0xFF);
  SDL_RenderDrawLines(sceneContext->renderer, points, nrPoints);
}

// Draw crosses & rects for board state
void GameSceneBoard::drawBoardState() {
  int **boardState = board->getState();
  for (int x = 0; x < board->getWidth(); x++) {
    for (int y = 0; y < board->getHeight(); y++) {
      Position boardPosition = {x, y};
      if (boardState[x][y] == 1) {
        drawCross(boardPosition, false);
      } else if (boardState[x][y] == 2) {
        drawRect(boardPosition, false);
      } else {
        // render preview texture
        int idx = y * board->getHeight() + x;
        Position screenPosition = boardPositionToScreenPosition(boardPosition);
        previewTextures[idx].render(sceneContext->renderer, screenPosition.x,
                                    screenPosition.y);
      }
    }
  }
}

GameSceneBoard::~GameSceneBoard() {
  fontTexture.free();
  previewTextures->free();
}