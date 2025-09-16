#include "Player.h"

Player::Player()
{
    mTexture = NULL;
    mPosX = 0;
    mPosY = 0;
}
Player::Player(int startX, int startY, int width, int height) // Currently not in use
{
    mTexture = NULL;
    mPosX = startX;
    mPosY = startY;
    mWidth = width;
    mHeight = height;
}
Player::~Player()
{
}
bool Player::loadAssets(SDL_Renderer *renderer, int *logLevel, int *messageDepth)
{
    printInfo(logLevel, messageDepth, "Initialising player...\n");
    (*messageDepth)++;
    printInfo(logLevel, messageDepth, "Making player texture...\n");
    (*messageDepth)++;
    mTexture = std::make_unique<Texture>(mImagePath);
    mTexture->loadTexture(renderer, mWidth, mHeight, logLevel, messageDepth);
    if (mTexture == NULL)
    {
        printDebug(logLevel, messageDepth, "Failed to create player texture.\n");
        return false;
    }
    (*messageDepth)--;
    printInfo(logLevel, messageDepth, "Player texture made.\n");
    (*messageDepth)--;

    printInfo(logLevel, messageDepth, "Player initialised.\n");
    return true;
}
void Player::close(int *logLevel, int *messageDepth)
{
    printInfo(logLevel, messageDepth, "Closing player...\n");
    (*messageDepth)++;
    mTexture->close(logLevel, messageDepth);
    (*messageDepth)--;
    printInfo(logLevel, messageDepth, "Player closed.\n");
}
void Player::render(SDL_Renderer *renderer)
{
    mTexture->render(renderer, mPosX, mPosY);
}
int Player::getXPosition() { return mPosX; }
int Player::getYPosition() { return mPosY; }