#pragma once
#include <engine/player/Player.hpp>

class AIPlayer : public Player {
    public: 
        AIPlayer(int &playerValue) : Player {playerValue} {}
        int getNextMove();
};