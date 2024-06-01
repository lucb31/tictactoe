#include <engine/player/RealPlayer.hpp>
#include <iostream>

int RealPlayer::getNextMove() {
  int position;
  std::cout << "Player " << getValue() << ": Choose your next position\n";
  std::cin >> position;
  return position;
}