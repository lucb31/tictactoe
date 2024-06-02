#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <gui/LTexture.hpp>

LTexture::~LTexture() {
  // Deallocate
  free();
}
void LTexture::free() {
  // Free texture if it exists
  if (mTexture == NULL) {
    return;
  }
  SDL_DestroyTexture(mTexture);
  mTexture = NULL;
  mWidth = 0;
  mHeight = 0;
}

void LTexture::setColor(Uint8 red, Uint8 green, Uint8 blue) {
  // Modulate texture rgb
  SDL_SetTextureColorMod(mTexture, red, green, blue);
}

void LTexture::setBlendMode(SDL_BlendMode blending) {
  // Set blending function
  SDL_SetTextureBlendMode(mTexture, blending);
}

void LTexture::setAlpha(Uint8 alpha) {
  // Modulate texture alpha
  SDL_SetTextureAlphaMod(mTexture, alpha);
}

void LTexture::render(SDL_Renderer* renderer, int x, int y, SDL_Rect* clip,
                      double angle, SDL_Point* center, SDL_RendererFlip flip) {
  // Set rendering space and render to screen
  SDL_Rect renderQuad = {x, y, mWidth, mHeight};

  // Set clip rendering dimensions
  if (clip != NULL) {
    renderQuad.w = clip->w;
    renderQuad.h = clip->h;
  }

  // Render to screen
  SDL_RenderCopyEx(renderer, mTexture, clip, &renderQuad, angle, center, flip);
}

int LTexture::getWidth() { return mWidth; }

int LTexture::getHeight() { return mHeight; }

bool LTexture::loadFromRenderedText(std::string textureText,
                                    SDL_Color textColor, TTF_Font* font,
                                    SDL_Renderer* renderer) {
  // Get rid of preexisting texture
  free();

  // Render text surface
  SDL_Surface* textSurface =
      TTF_RenderText_Solid(font, textureText.c_str(), textColor);
  if (textSurface == NULL) {
    printf("Unable to render text surface! SDL_ttf Error: %s\n",
           TTF_GetError());
    return false;
  }
  // Create texture from surface pixels
  mTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
  if (mTexture == NULL) {
    printf("Unable to create texture from rendered text! SDL Error: %s\n",
           SDL_GetError());
    return false;
  }
  // Get image dimensions
  mWidth = textSurface->w;
  mHeight = textSurface->h;

  // Get rid of old surface
  SDL_FreeSurface(textSurface);

  // Return success
  return mTexture != NULL;
}