#include "Item.h"

#include "Texture.h"

Item::Item()
{
    mTextureSheet = std::make_unique<Texture>();
    mClip = {0, 0, 0, 0};
    mHitbox = {0, 0, 0, 0};
}
Item::~Item()
{
}
bool Item::init(SDL_Renderer *renderer, const int *logLevel, int *messageDepth, const int x, const int y, const int width, const int height, const int texturesheetX, const int texturesheetY, const int scale = 1)
{
    mHitbox.x = x;
    mHitbox.y = y;
    mHitbox.w = width;
    mHitbox.h = height;
    mClip = {texturesheetX * width, texturesheetY * height, width, height};
    mScale = scale;

    return loadTexture(renderer, logLevel, messageDepth);
}
void Item::renderOnScreen(SDL_Renderer *renderer)
{
    mTextureSheet->render(renderer, mHitbox.x, mHitbox.y, &mClip, mScale);
}
void Item::renderOnGround(SDL_Renderer *renderer, SDL_Rect &camera)
{
    if (Global::areColliding(mHitbox, camera))
        mTextureSheet->render(renderer, mHitbox.x - camera.x, mHitbox.y - camera.y, &mClip, mScale);
}
void Item::setX(const int x) { mHitbox.x = x; }
void Item::setY(const int y) { mHitbox.y = y; }
int Item::getSidelength() { return mHitbox.w; }
SDL_Rect Item::getHitBox() { return mHitbox; }

bool Item::loadTexture(SDL_Renderer *renderer, const int *logLevel, int *messageDepth)
{
    return mTextureSheet->loadTexture(mImagePath, renderer, mHitbox.w, mHitbox.h, logLevel, messageDepth);
}