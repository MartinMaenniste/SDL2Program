#include "Texture.h"

Texture::Texture()
{
    mImagePath = nullptr;
    mTexture = NULL;
    mTextureWidth = 0;
    mTextureHeight = 0;
}
Texture::~Texture()
{
}

bool Texture::loadTextureFromPath(const char *pathToImage, SDL_Renderer *renderer, const int width, const int height, const int *logLevel, int *messageDepth)
{
    mTextureWidth = width;
    mTextureHeight = height;
    mImagePath = pathToImage;

    mTexture = IMG_LoadTexture(renderer, mImagePath);
    if (mTexture == NULL)
    {
        Global::printDebug(logLevel, messageDepth, "Failed to load texture: ");
        if ((*logLevel) > 0)
        {
            printf("%s\n", IMG_GetError());
        }
        return false;
    }
    return true;
}
bool Texture::loadTextureFromSurface(const char *pathToImage, SDL_Surface *surface, SDL_Renderer *renderer, const int width, const int height, const int *logLevel, int *messageDepth)
{
    mTextureWidth = width;
    mTextureHeight = height;
    mImagePath = pathToImage;
    mTexture = SDL_CreateTextureFromSurface(renderer, surface);
    if (mTexture == NULL)
    {
        Global::printDebug(logLevel, messageDepth, "Could not create texture from surface: ");
        if ((*logLevel) > 0)
        {
            printf("%s\n", SDL_GetError());
        }
        return false;
    }
    return true;
}
void Texture::render(SDL_Renderer *renderer, const int x, const int y, const SDL_Rect *clip, const int scale, const double angle, const SDL_Point *center, const SDL_RendererFlip flip)
{
    SDL_Rect textureClip = {x, y, mTextureWidth * scale, mTextureHeight * scale};
    SDL_RenderCopyEx(renderer, mTexture, clip, &textureClip, angle, center, flip);
}
void Texture::close(const int *logLevel, int *messageDepth)
{
    Global::printInfo(logLevel, messageDepth, "Destroying texture...\n");
    SDL_DestroyTexture(mTexture);
    Global::printInfo(logLevel, messageDepth, "Texture destroyed.\n");
}
