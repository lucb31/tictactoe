#pragma once
#include <SDL2/SDL_timer.h>

class LTimer {
 private:
  // Tick of timer start
  Uint32 mStartTicks = 0;
  // Tick of pause timer start
  Uint32 mPausedTicks = 0;

  bool mPaused = false;
  bool mStarted = false;

 public:
  void start();
  void stop();
  void pause();
  void unpause();

  Uint32 getTicks();

  bool isStarted();
  bool isPaused();
};