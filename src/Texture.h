#include "globalFunctions.h"

class Texture
{
public:
    Texture();
    ~Texture();

    bool loadTextureFromPath(const char *pathToImage, SDL_Renderer *renderer, int width, int height, int *logLevel, int *messageDepth);
    bool loadTextureFromSurface(const char *pathToImage, SDL_Surface *surface, SDL_Renderer *renderer, int width, int height, int *logLevel, int *messageDepth);
    void render(SDL_Renderer *renderer, int x, int y, SDL_Rect *clip = NULL, double angle = 0.0, SDL_Point *center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
    void close(int *logLevel, int *messageDepth);

private:
    SDL_Texture *mTexture;
    const char *mImagePath;
    int mTextureWidth, mTextureHeight;
};