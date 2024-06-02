#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>

#include <string>

// Texture wrapper class
class LTexture {
 public:
  // Initializes variables
  // LTexture();

  // Deallocates memory
  ~LTexture();

  // Loads image at specified path
  bool loadFromFile(std::string path);

  // Creates image from font string
  bool loadFromRenderedText(std::string textureText, SDL_Color textColor,
                            TTF_Font* font, SDL_Renderer* renderer);

  // Deallocates texture
  void free();

  // Set color modulation
  void setColor(Uint8 red, Uint8 green, Uint8 blue);

  // Set blending
  void setBlendMode(SDL_BlendMode blending);

  // Set alpha modulation
  void setAlpha(Uint8 alpha);

  // Renders texture at given point
  void render(SDL_Renderer* renderer, int x, int y, SDL_Rect* clip = NULL,
              double angle = 0.0, SDL_Point* center = NULL,
              SDL_RendererFlip flip = SDL_FLIP_NONE);

  // Gets image dimensions
  int getWidth();
  int getHeight();

 private:
  // The actual hardware texture
  SDL_Texture* mTexture = NULL;

  // Image dimensions
  int mWidth = 0;
  int mHeight = 0;
};