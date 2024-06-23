#include <SDL2/SDL_timer.h>

#include <gui/LTimer.hpp>

void LTimer::start() {
  mStarted = true;
  mPaused = false;

  mStartTicks = SDL_GetTicks();
  mPausedTicks = 0;
}

void LTimer::stop() {
  mStarted = false;
  mPaused = false;

  mStartTicks = 0;
  mPausedTicks = 0;
}

void LTimer::pause() {
  if (!mStarted || mPaused) return;

  mPaused = true;
  mPausedTicks = SDL_GetTicks() - mStartTicks;
  mStartTicks = 0;
}

void LTimer::unpause() {
  if (!mStarted || !mPaused) return;

  mPaused = false;
  mStartTicks = SDL_GetTicks() - mPausedTicks;
  mPausedTicks = 0;
}

Uint32 LTimer::getTicks() {
  if (!mStarted) return 0;

  if (mPaused) {
    // Return TT when the timer was paused
    return mPausedTicks;
  }
  // Return current time - start time
  return SDL_GetTicks() - mStartTicks;
}

bool LTimer::isStarted() { return mStarted; }

bool LTimer::isPaused() { return mStarted && mPaused; }