#include <iostream>
#include "Board.hpp"
#include "AIPlayer.hpp"

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
    // Greet user
    greet_user();

    // Initialize board
    srand (time(NULL));
    int val1 = 1;
    int val2 = 2;
    AIPlayer player1(val1);
    AIPlayer player2(val2);
    Board myBoard(&player1, &player2);

    myBoard.printState(); 

    while (!myBoard.isOver()) {
        myBoard.nextTurn();
    }
    
    std::cout<<"Game Over\n";

    return 0;
}