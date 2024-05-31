#include <iostream>
#include <tuple>
#include "Board.hpp"

// Currently will just randomly set a field
void Board::nextTurn() {
    int playerIndex = currentTurn % 2 + 1;
    // Todo: Determine via user input
    int position = rand() % 9 + 1;

    std::cout<<"Turn "<<currentTurn<<": Player "<<playerIndex<<" choosing position "<<position<<"\n";
    bool turnExecuted = false;
    while (!turnExecuted){
        try {
            setField(position, playerIndex);
            turnExecuted = true;
        } catch(const std::invalid_argument& e) {
            position = rand() % 9 + 1;
        }
    }
    printState(); 
    currentTurn++;
}

void Board::setField(int const &position, int const &playerIndex) {
    // Check availability: Throw error if trying to set a field that is already occupied
    auto [x, y] = posToXY(position);
    if (gameState[x][y] != 0) {
        throw std::invalid_argument("Cannot assign field: Already occupied");
    }

    // Update game state
    gameState[x][y] = playerIndex;
}


void Board::printState() {
    std::cout<<"--------------BOARD STATE START--------------\n";
    int rows = sizeof gameState / sizeof gameState[0];
    for (int x = 0; x < rows; x++) {
        for (int y = 0; y < sizeof gameState[0] / sizeof(int); y++) {
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
                std::cout << posFromXY(x,y);
            }
            
            std::cout << " |";
        }
        std::cout<<"\n";
        
    }
    std::cout<<"--------------BOARD STATE END--------------\n\n";
}

/*
Return player index of winner

Returns 0 if no player won
*/
int Board::getWinner() {
    // Check for row wins
    for (int x = 0; x < 3; x++) {
        bool isEqual = true;
        int &currentValue = gameState[x][0];
        for (int y = 1; y < 3; y++) {
            if (gameState[x][y] != currentValue) {
                isEqual = false;
            }
        }
        if (isEqual) {
            return currentValue;
        }
    }
    // Check for col wins
    for (int y = 0; y < 3; y++) {
        bool isEqual = true;
        int &currentValue = gameState[0][y];
        for (int x = 1; x < 3; x++) {
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
    if (gameState[0][0] == centerValue && gameState[2][2] == centerValue||
        gameState[0][2] == centerValue && gameState[2][0] == centerValue) {
        return centerValue;
    }

    return 0;
}

bool Board::isOver() {
    int winner = getWinner();
    // Determine win condition
    if (getWinner() > 0) {
        std::cout<<"WINNER: Player "<<winner<<"\n";

        return true;
    }

    // Game is over when all fields are occupied
    return !hasVacantFields();
}

bool Board::hasVacantFields() {
    int rows = sizeof gameState / sizeof gameState[0];
    for (int x = 0; x < rows; x++) {
        for (int y = 0; y < sizeof gameState[0] / sizeof(int); y++) {
            if (gameState[x][y] == 0) {
                return true;
            }
        }
    }
    return false;
}

// UTILITY
std::tuple<int, int> Board::posToXY(int const &position) {
    // Convert position to x,y
    int rows = sizeof gameState / sizeof gameState[0];
    int x = (position - 1) / rows;
    int y = (position - 1) % rows;

    return std::make_tuple(x,y);
} 

int Board::posFromXY(int const &x, int const &y) {
    int rows = sizeof gameState / sizeof gameState[0];
    return x*rows + y + 1;
}