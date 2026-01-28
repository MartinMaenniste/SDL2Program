#include "Interactable.h"
#include "Texture.h"

Interactable::Interactable()
{
    mTextureSheet = std::make_unique<Texture>();
    mSolidHitbox = {0, 0, 80, 30};
    mFullHitbox = {0, 0, 80, 120};
    mSheetRect = {0, 0, 80, 120};
    mRenderTransparent = false;
}
Interactable::Interactable(const int x, const int y)
{
    mSolidHitbox = {x, y, 80, 30};
    mFullHitbox = {x, y+(120-30), 80, 120};
    mSheetRect = {0, 0, 80, 120};
    mRenderTransparent = false;
}
Interactable::~Interactable()
{
    
}
bool Interactable::init(SDL_Renderer* renderer, const int x, const int y, const int* logLevel, int* messageDepth, bool canWalkThrough)
{
    mFullHitbox.x = x;
    mFullHitbox.y = y;

    mSolidHitbox.x = x;
    mSolidHitbox.y = y + (mFullHitbox.h - mSolidHitbox.h);

    mCanWalkThrough = canWalkThrough;

    return loadTexture(renderer, logLevel, messageDepth);
}
void Interactable::update(SDL_Rect playerHitbox)
{
    if(Global::areColliding(mFullHitbox, playerHitbox))
        mRenderTransparent = true;
    else
        mRenderTransparent = false;
}
void Interactable::render(SDL_Renderer* renderer, SDL_Rect &camera)
{
    if (Global::areColliding(mFullHitbox, camera))
    {
        if (mRenderTransparent)
            mTextureSheet->setAlpha(200);
        else
            mTextureSheet->setAlpha(255);
        mTextureSheet->render(renderer, mFullHitbox.x - camera.x, mFullHitbox.y - camera.y, &mSheetRect);
    }
}
bool Interactable::getCanWalkThrough() {return mCanWalkThrough;}
SDL_Rect Interactable::getHitbox() {return mSolidHitbox;}

bool Interactable::loadTexture(SDL_Renderer* renderer, const int* logLevel, int* messageDepth)
{
    return mTextureSheet->loadTexture(mPathToTextureSheet, renderer, mSheetRect.w, mSheetRect.h, logLevel, messageDepth);
}