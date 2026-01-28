#pragma once

//#include "Texture.h"
#include "GlobalFunctions.h"
class Texture;

class Item
{
public:
    Item();
    ~Item();

    bool init(SDL_Renderer *renderer, const int *logLevel, int *messageDepth, const int x, const int y, const int width, const int height, const int texturesheetX, const int texturesheetY, const int scale);
    void renderOnScreen(SDL_Renderer *renderer);                   // Render function used for rendering on ui
    void renderOnGround(SDL_Renderer *renderer, SDL_Rect &camera); // Only render if inside the camera.

    void setX(const int x);
    void setY(const int y);

    int getSidelength();
    SDL_Rect getHitBox();

private:
    // Items can be on ground, in inventory or stored away somewhere - chests or such, for future development.
    std::unique_ptr<Texture> mTextureSheet;
    const char *mImagePath = "./assets/Item.png";
    SDL_Rect mClip;
    SDL_Rect mHitbox;
    int mScale;

    bool loadTexture(SDL_Renderer *renderer, const int *logLevel, int *messageDepth);
};