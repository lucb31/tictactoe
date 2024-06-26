#include <engine/Board.hpp>
#include <engine/player/AIPlayer.hpp>
#include <engine/player/Player.hpp>
#include <engine/player/RealPlayer.hpp>
#include <iostream>
#include <tuple>

Board::Board() {
  initializePlayers();
  initializeMap();
}

void Board::initializePlayers() {
  int val1 = 1;
  int val2 = 2;

  int choice = 1;
  // std::cout << "Please choose if you want to play \n";
  // std::cout << "  0: Human vs Human\n";
  // std::cout << "  1: Human vs AI\n";
  // std::cout << "  2: AI vs AI\n";
  // std::cin >> choice;
  switch (choice) {
    case 0:
      player1 = new RealPlayer(val1);
      player2 = new RealPlayer(val2);
      break;
    case 1:
      player1 = new RealPlayer(val1);
      player2 = new AIPlayer(val2);
      break;
    default:
      player1 = new AIPlayer(val1);
      player2 = new AIPlayer(val2);
      break;
  }
  updateActivePlayer();
}

void Board::initializeMap() {
  gameState = new int *[N_COLS];
  for (int x = 0; x < N_COLS; x++) {
    gameState[x] = new int[N_ROWS];
    for (int y = 0; y < N_ROWS; y++) {
      gameState[x][y] = 0;
    }
  }
}

Player *Board::getActivePlayer() {
  if (currentTurn % 2 == 0) {
    return player1;
  }
  return player2;
}

void Board::updateActivePlayer() {
  if (currentTurn % 2 == 0) {
    player1->setActive();
    player2->setInactive();
    return;
  }
  player1->setInactive();
  player2->setActive();
}

bool Board::nextTurn() {
  // Determine active player
  Player *activePlayer = getActivePlayer();

  // Determine desired position
  int position = activePlayer->getNextMove();
  // Exit if invalid position
  if (position <= 0) {
    return false;
  }
  std::cout << "Turn " << currentTurn << ", Player " << activePlayer->getValue()
            << ": Choose position " << position << "\n";

  // Try to occupy field
  try {
    setField(position, activePlayer->getValue());
  } catch (const std::invalid_argument &e) {
    std::cout << "Player " << activePlayer->getValue() << " move to position "
              << position << " denied: Field already occupied\n";
    return false;
  }
  currentTurn++;
  updateActivePlayer();

  return true;
}

void Board::setField(int const &position, int const &playerIndex) {
  // Check availability: Throw error if trying to set a field that is already
  // occupied
  auto [x, y] = posToXY(position);
  if (gameState[x][y] != 0) {
    throw std::invalid_argument("Cannot assign field: Already occupied");
  }

  // Update game state
  gameState[x][y] = playerIndex;
}

/*
Return player index of winner

Returns 0 if no player won
*/
int Board::getWinner() {
  // Check for row wins
  for (int x = 0; x < N_COLS; x++) {
    bool isEqual = true;
    int &currentValue = gameState[x][0];
    for (int y = 1; y < N_ROWS; y++) {
      if (gameState[x][y] != currentValue) {
        isEqual = false;
      }
    }
    // All cols equal in this row and not unoccupied
    if (isEqual && currentValue > 0) {
      std::cout << "WINNER by rows: Player " << currentValue << "\n";
      return currentValue;
    }
  }
  // Check for col wins
  for (int y = 0; y < N_ROWS; y++) {
    bool isEqual = true;
    int &currentValue = gameState[0][y];
    for (int x = 1; x < N_COLS; x++) {
      if (gameState[x][y] != currentValue) {
        isEqual = false;
      }
    }
    // All rows equal in this col and not unoccupied
    if (isEqual && currentValue > 0) {
      std::cout << "WINNER by cols: Player " << currentValue << "\n";
      return currentValue;
    }
  }
  // Check diagonals
  int &centerValue = gameState[1][1];
  if (centerValue > 0 &&
      (gameState[0][0] == centerValue && gameState[2][2] == centerValue ||
       gameState[0][2] == centerValue && gameState[2][0] == centerValue)) {
    std::cout << "WINNER by diagonals: Player " << centerValue << "\n";
    return centerValue;
  }

  return 0;
}

bool Board::isOver() {
  // Update winner
  if (winner == 0) {
    winner = getWinner();
  }
  if (winner > 0) {
    return true;
  }

  // Game is over when all fields are occupied
  return !hasVacantFields();
}

bool Board::hasVacantFields() {
  for (int x = 0; x < N_COLS; x++) {
    for (int y = 0; y < N_ROWS; y++) {
      if (gameState[x][y] == 0) {
        return true;
      }
    }
  }
  std::cout << "No more vacant fields!\n";
  return false;
}

// UTILITY
// Convert position to x,y
std::tuple<int, int> Board::posToXY(int const &position) {
  int x = (position - 1) % N_ROWS;
  int y = (position - 1) / N_ROWS;

  return std::make_tuple(x, y);
}

int Board::posFromXY(int const &x, int const &y) { return x * N_ROWS + y + 1; }

const int Board::getField(const int &position) {
  auto [x, y] = posToXY(position);

  return gameState[x][y];
}