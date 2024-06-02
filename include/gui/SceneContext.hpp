#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

struct SceneContext {
  // SDL Dependencies
  SDL_Renderer* renderer;
  TTF_Font* gFont;

  // Screen dimension constants
  const int screenWidth;
  const int screenHeight;
};
