#include <stdlib.h>
#include <engine/player/AIPlayer.hpp>

int AIPlayer::getNextMove() {
    return rand() % 9 + 1;
}