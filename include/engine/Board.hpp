#pragma once
#include <engine/player/Player.hpp>

class Board {
    int N_ROWS;
    int N_COLS;
    /*
    0 = Unset
    1 = Player 1
    2 = Player 2
    */
    int** gameState;
    int currentTurn = 0;
    Player *player1;
    Player *player2;

    public: 
        Board(Player *player1, Player *player2, const int &width = 3, const int &height = 3) 
        : player1(player1), player2(player2), N_ROWS(height), N_COLS(width) {
            // Initialize board map
            gameState = new int*[width];
            for (int x = 0; x < width; x++) {
                gameState[x] = new int[height];
                for (int y = 0; y < height; y++) {
                    gameState[x][y] = 0;
                }
            }
        }
        int** getState() {
            return gameState;
        }
        void nextTurn();

        void setField(int const &position, int const &playerIndex);

        void printState();

        bool isOver();
    private:
        int getWinner();
        bool hasVacantFields();
        std::tuple<int, int> posToXY(int const &position);
        int posFromXY(int const &x, int const &y);

};