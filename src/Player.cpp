#include "Player.h"

Player::Player()
{
    mTexture = NULL;
    mPosX = 0;
    mPosY = 0;
    mWidth = 0;
    mHeight = 0;
    mPlayerSpeedMAX = 0;
    mPlayerAcceleration = 0;
    mTexture = std::make_unique<Texture>();
}
Player::Player(int startX, int startY, int width, int height)
{
    mTexture = NULL;
    mPosX = startX;
    mPosY = startY;
    mWidth = width;
    mHeight = height;
    mPlayerSpeedMAX = 10; // TODO - make a better system
    mPlayerAcceleration = 1;
    mTexture = std::make_unique<Texture>();
}
Player::~Player()
{
}
bool Player::loadAssets(SDL_Renderer *renderer, int *logLevel, int *messageDepth)
{
    printInfo(logLevel, messageDepth, "Initialising player...\n");
    (*messageDepth)++;

    // Since I want to be the background colour of the sprite transparent, load it to surface first and when pixel manipulation is over, then to texture.
    printInfo(logLevel, messageDepth, "Making player surface...\n");
    (*messageDepth)++;
    SDL_Surface *imageSurface = IMG_Load(mImagePath);
    SDL_SetColorKey(imageSurface, SDL_TRUE, SDL_MapRGB(imageSurface->format, 1, 255, 1));
    if (imageSurface == NULL)
    {
        printDebug(logLevel, messageDepth, "Could not make player surface: ");
        if ((*logLevel) > 0)
        {
            printf("%s\n", IMG_GetError());
        }
        return false;
    }
    (*messageDepth)--;
    printInfo(logLevel, messageDepth, "Player surface made.\n");

    printInfo(logLevel, messageDepth, "Making player texture...\n");
    (*messageDepth)++;
    mTexture->loadTextureFromSurface(mImagePath, imageSurface, renderer, mWidth, mHeight, logLevel, messageDepth);
    if (mTexture == NULL)
    {
        printDebug(logLevel, messageDepth, "Failed to create player texture.\n");
        return false;
    }
    (*messageDepth)--;
    printInfo(logLevel, messageDepth, "Player texture made.\n");
    (*messageDepth)--;

    SDL_FreeSurface(imageSurface);
    imageSurface = nullptr;

    printInfo(logLevel, messageDepth, "Player initialised.\n");
    return true;
}
void Player::handleEvents(SDL_Event &event)
{
    if (event.type == SDL_KEYDOWN && event.key.repeat == 0)
    {
        switch (event.key.keysym.sym)
        {
        case SDLK_w:
            mYMotion -= 1;
            break;
        case SDLK_s:
            mYMotion += 1;
            break;
        case SDLK_a:
            mXMotion -= 1;
            break;
        case SDLK_d:
            mXMotion += 1;
            break;

        default:
            break;
        }
    }
    else if (event.type == SDL_KEYUP && event.key.repeat == 0)
    {
        switch (event.key.keysym.sym)
        {
        case SDLK_w:
            mYMotion += 1;
            break;
        case SDLK_s:
            mYMotion -= 1;
            break;
        case SDLK_a:
            mXMotion += 1;
            break;
        case SDLK_d:
            mXMotion -= 1;
            break;

        default:
            break;
        }
    }
}
void Player::move(int &levelWidth, int &levelHeight)
{
    updateVelocity();
    updatePos(levelWidth, levelHeight);
}
void Player::render(std::unique_ptr<Window> &window, int cameraX, int cameraY)
{
    mTexture->render(window->getRenderer(), mPosX - cameraX, mPosY - cameraY);
}
void Player::close(int *logLevel, int *messageDepth)
{
    printInfo(logLevel, messageDepth, "Closing player...\n");
    (*messageDepth)++;
    mTexture->close(logLevel, messageDepth);
    (*messageDepth)--;
    printInfo(logLevel, messageDepth, "Player closed.\n");
}
int Player::getXPosition() { return mPosX; }
int Player::getYPosition() { return mPosY; }
int Player::getWidth() { return mWidth; }
int Player::getHeight() { return mHeight; }

void Player::updateVelocity()
{
    updateXVelocity();
    updateYVelocity();
}
void Player::updateXVelocity()
{
    if (mXMotion == 0)
    {
        // If the player should be stationary, slow player down
        if (abs(mVelX) == 1 || abs(mVelX) == 0)
            mVelX = 0;
        else
            mVelX > 0 ? mVelX -= mPlayerAcceleration : mVelX += mPlayerAcceleration;
    }
    else
    {
        // Otherwise speed up, player should be moving in mXMotion's direction
        mVelX += mXMotion * mPlayerAcceleration;
    }

    // Make sure to cap speed!

    if (mVelX > mPlayerSpeedMAX)
    {
        mVelX = mPlayerSpeedMAX;
    }
    else if (mVelX < -1 * mPlayerSpeedMAX)
    {
        mVelX = -1 * mPlayerSpeedMAX;
    }
}
void Player::updateYVelocity()
{
    if (mYMotion == 0)
    {
        // If the player should be stationary, slow player down
        if (abs(mVelY) == 1 || abs(mVelY) == 0)
            mVelY = 0;
        else
            mVelY > 0 ? mVelY -= mPlayerAcceleration : mVelY += mPlayerAcceleration;
    }
    else
    {
        // Otherwise speed up, player should be moving in mYMotion's direction
        mVelY += mYMotion * mPlayerAcceleration;
    }

    // Make sure to cap speed!

    if (mVelY > mPlayerSpeedMAX)
    {
        mVelY = mPlayerSpeedMAX;
    }
    else if (mVelY < -1 * mPlayerSpeedMAX)
    {
        mVelY = -1 * mPlayerSpeedMAX;
    }
}
void Player::updatePos(int &levelWidth, int &levelHeight)
{
    mPosX += mVelX;
    mPosY += mVelY;

    if (mPosX < 0)
    {
        mPosX = 0;
    }
    else if (mPosX + mWidth > levelWidth)
    {
        mPosX = levelWidth - mWidth;
    }

    if (mPosY < 0)
    {
        mPosY = 0;
    }
    else if (mPosY + mHeight > levelHeight)
    {
        mPosY = levelHeight - mHeight;
    }
}