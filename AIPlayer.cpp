#include "AIPlayer.hpp"
#include <stdlib.h>

int AIPlayer::getNextMove() {
    return rand() % 9 + 1;
}