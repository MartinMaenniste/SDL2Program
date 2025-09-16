#include "Texture.h"

Texture::Texture(const char *pathToImage)
{
    mImagePath = pathToImage;
    mTexture = NULL;
    mTextureWidth = 0;
    mTextureHeight = 0;
}
Texture::~Texture()
{
}

bool Texture::loadTexture(SDL_Renderer *renderer, int width, int height, int *logLevel, int *messageDepth)
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