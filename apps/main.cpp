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
    int val1 = 1;
    int val2 = 2;
    Player *player1;
    Player *player2;

    // Initialize players
    int choice;
    std::cout<<"Please choose if you want to play \n";
    std::cout<<"  0: Human vs Human\n";
    std::cout<<"  1: Human vs AI\n";
    std::cout<<"  2: AI vs AI\n";
    std::cin>>choice;
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

    // Init board
    Board myBoard(player1, player2);

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