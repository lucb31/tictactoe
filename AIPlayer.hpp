#pragma once
#include "Player.hpp"

class AIPlayer : public Player {
    public: 
        AIPlayer(int &playerValue) : Player {playerValue} {}
        int getNextMove();
};