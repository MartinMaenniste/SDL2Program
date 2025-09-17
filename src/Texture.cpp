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

bool Texture::loadTextureFromPath(const char *pathToImage, SDL_Renderer *renderer, int width, int height, int *logLevel, int *messageDepth)
{
    mTextureWidth = width;
    mTextureHeight = height;
    mTexture = IMG_LoadTexture(renderer, mImagePath);
    if (mTexture == NULL)
    {
        printDebug(logLevel, messageDepth, "Failed to load texture: ");
        if ((*logLevel) > 0)
        {
            printf("%s\n", IMG_GetError());
        }
        return false;
    }
    return true;
}
bool Texture::loadTextureFromSurface(const char *pathToImage, SDL_Surface *surface, SDL_Renderer *renderer, int width, int height, int *logLevel, int *messageDepth)
{
    mTextureWidth = width;
    mTextureHeight = height;
    mImagePath = pathToImage;
    mTexture = SDL_CreateTextureFromSurface(renderer, surface);
    if (mTexture == NULL)
    {
        printDebug(logLevel, messageDepth, "Could not create texture from surface: ");
        if ((*logLevel) > 0)
        {
            printf("%s\n", SDL_GetError());
        }
        return false;
    }
    return true;
}
void Texture::render(SDL_Renderer *renderer, int x, int y, SDL_Rect *clip, double angle, SDL_Point *center, SDL_RendererFlip flip)
{
    SDL_Rect textureClip = {x, y, mTextureWidth, mTextureHeight};
    if (clip != NULL)
    {
        textureClip.w = clip->w;
        textureClip.h = clip->h;
    }
    SDL_RenderCopyEx(renderer, mTexture, clip, &textureClip, angle, center, flip);
}
void Texture::close(int *logLevel, int *messageDepth)
{
    printInfo(logLevel, messageDepth, "Destroying texture...\n");
    SDL_DestroyTexture(mTexture);
    printInfo(logLevel, messageDepth, "Texture destroyed.\n");
}