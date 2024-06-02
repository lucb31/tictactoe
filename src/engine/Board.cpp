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

  int choice = 3;
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

void Board::nextTurn() {
  std::cout << "Turn " << currentTurn << "\n";
  // Determine active player
  Player *activePlayer = getActivePlayer();

  // Determine desired position
  int position = activePlayer->getNextMove();
  std::cout << "Player " << activePlayer->getValue() << " choosing position "
            << position << "\n";

  // Try to occupy field & re-determine position if unsucessful
  bool turnExecuted = false;
  while (!turnExecuted) {
    try {
      setField(position, activePlayer->getValue());
      turnExecuted = true;
    } catch (const std::invalid_argument &e) {
      position = activePlayer->getNextMove();
    }
  }
  printState();
  currentTurn++;
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

void Board::printState() {
  std::cout << "--------------BOARD STATE START--------------\n";
  for (int x = 0; x < N_COLS; x++) {
    for (int y = 0; y < N_ROWS; y++) {
      std::cout << " ";
      int &current = gameState[x][y];
      // Player 1
      if (current == 1) {
        std::cout << "X";
      }
      // Player 2
      else if (current == 2) {
        std::cout << "O";
      }
      // Print position to be occupied
      else {
        std::cout << posFromXY(x, y);
      }

      std::cout << " |";
    }
    std::cout << "\n";
  }
  std::cout << "--------------BOARD STATE END--------------\n\n";
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
    if (isEqual) {
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
    if (isEqual) {
      return currentValue;
    }
  }
  // Check diagonals
  int &centerValue = gameState[1][1];
  if (gameState[0][0] == centerValue && gameState[2][2] == centerValue ||
      gameState[0][2] == centerValue && gameState[2][0] == centerValue) {
    return centerValue;
  }

  return 0;
}

bool Board::isOver() {
  int winner = getWinner();
  // Determine win condition
  if (getWinner() > 0) {
    std::cout << "WINNER: Player " << winner << "\n";

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
  int x = (position - 1) / N_ROWS;
  int y = (position - 1) % N_ROWS;

  return std::make_tuple(x, y);
}

int Board::posFromXY(int const &x, int const &y) { return x * N_ROWS + y + 1; }