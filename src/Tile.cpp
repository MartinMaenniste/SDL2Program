#include "Tile.h"

Tile::Tile()
{
    SDL_Rect mStylesheetRect = {0,0,0,0};
    SDL_Rect mHitbox = {0,0,0,0};
    bool mCanWalkThrough = true;
    int mScale = 1;
}
void Tile::render(SDL_Renderer* renderer, SDL_Rect& cameraRect, std::unique_ptr<Texture>& stylesheetTexture, int& scale)
{
    if (!Global::areColliding(mHitbox, cameraRect)) return;
    stylesheetTexture->render(renderer, mHitbox.x - cameraRect.x, mHitbox.y - cameraRect.y, &mStylesheetRect, scale);
}
void Tile::setValues(const int stylesheetX, const int stylesheetY, const int sideLength, const bool canWalkthrough, const int posX, const int posY, const int scale)
{
    mStylesheetRect.x = stylesheetX;
    mStylesheetRect.y = stylesheetY;
    mStylesheetRect.w = sideLength;
    mStylesheetRect.h = sideLength;

    mCanWalkThrough = canWalkthrough;

    mHitbox.x = posX;
    mHitbox.y = posY;
    mHitbox.w = mStylesheetRect.w;
    mHitbox.h = mStylesheetRect.h;
}
bool Tile::getWalkThrough() { return mCanWalkThrough; }
SDL_Rect Tile::getHitbox() { return mHitbox; }