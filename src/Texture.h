#pragma once

#include "GlobalFunctions.h"

class Texture
{
public:
    Texture();
    ~Texture();

    bool loadTexture(const char *pathToImage, SDL_Renderer *renderer, const int width, const int height, const int *logLevel, int *messageDepth);

    void setAlpha(const int value);
    void render(SDL_Renderer *renderer, const int x, const int y, const SDL_Rect *clip = NULL, const int scale = 1, const double angle = 0.0, const SDL_Point *center = NULL, const SDL_RendererFlip flip = SDL_FLIP_NONE);
    void close(const int *logLevel, int *messageDepth);

private:
    SDL_Texture *mTexture;
    const char *mImagePath;
    int mTextureWidth, mTextureHeight;
};