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
bool Texture::loadTexture(const char *pathToImage, SDL_Renderer *renderer, const int width, const int height, const int *logLevel, int *messageDepth)
{
    mTextureWidth = width;
    mTextureHeight = height;
    mImagePath = pathToImage;

    // Since I want to be the background colour of the sprite transparent, load it to surface first and when pixel manipulation is over, then convert to texture.
    Global::printInfo(logLevel, messageDepth, "Making texture surface...\n");
    (*messageDepth)++;

    SDL_Surface *imageSurface = IMG_Load(mImagePath);
    SDL_SetColorKey(imageSurface, SDL_TRUE, SDL_MapRGB(imageSurface->format, 1, 255, 1));
    if (imageSurface == NULL)
    {
        Global::printDebug(logLevel, messageDepth, "Could not texture surface surface.\n");
        if ((*logLevel) > 0)
        {
            printf("%s\n", IMG_GetError());
        }
        return false;
    }
    (*messageDepth)--;
    Global::printInfo(logLevel, messageDepth, "Texture surface made.\n");

    Global::printInfo(logLevel, messageDepth, "Making texture from surface...\n");
    mTexture = SDL_CreateTextureFromSurface(renderer, imageSurface);

    SDL_FreeSurface(imageSurface);
    imageSurface = nullptr;

    if (mTexture == NULL)
    {
        Global::printDebug(logLevel, messageDepth, "Could not create texture from surface: ");
        if ((*logLevel) > 0)
        {
            printf("%s\n", SDL_GetError());
        }
        return false;
    }
    SDL_SetTextureBlendMode(mTexture, SDL_BLENDMODE_BLEND);

    Global::printInfo(logLevel, messageDepth, "Texture made.\n");
    return true;
}
void Texture::setAlpha(const int value)
{
    SDL_SetTextureAlphaMod(mTexture, value);
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
