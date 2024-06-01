#include <iostream>
#include <engine/Board.hpp>
#include <engine/player/AIPlayer.hpp>
#include <engine/player/RealPlayer.hpp>

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

int main( int argc, char* args[] ) {
    // Setup
    srand (time(NULL));

    // Init board
    Board myBoard;

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