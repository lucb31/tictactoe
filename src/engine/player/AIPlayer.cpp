#include <stdlib.h>

#include <engine/player/AIPlayer.hpp>

void AIPlayer::handleKeyPress(SDL_Event* e) { nextMove = rand() % 9 + 1; }