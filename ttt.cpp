#include <iostream>
#include "Board.hpp"
#include "AIPlayer.hpp"
#include "RealPlayer.hpp"

/*
Iterations:
V1: Solo vs Random AI
*/

/*
Output introduction message + Instructions on how to play.
*/
void greet_user() {
    std::cout<<"Welcome to Tic-Tac-Toe. Further instructions will follow \n";
}

int main() {
    // Setup
    srand (time(NULL));
    // Initialize board
    int val1 = 1;
    int val2 = 2;
    RealPlayer player1(val1);
    RealPlayer player2(val2);
    Board myBoard(&player1, &player2);

    // Greet user
    greet_user();

    // Game loop
    myBoard.printState(); 
    while (!myBoard.isOver()) {
        myBoard.nextTurn();
    }
    
    std::cout<<"Game Over\n";

    return 0;
}