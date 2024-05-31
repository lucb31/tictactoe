#pragma once
#include "Player.hpp"

class RealPlayer : public Player {
    public: 
        RealPlayer(int &playerValue) : Player {playerValue} {}
        int getNextMove();
};