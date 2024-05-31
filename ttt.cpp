#include <iostream>
#include "Board.hpp"

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
    Board myBoard;

    myBoard.printState(); 

    while (!myBoard.isOver()) {
        myBoard.nextTurn();
    }
    
    std::cout<<"Game Over\n";

    return 0;
}

class Player {};