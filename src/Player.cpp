#include "Player.h"

Player::Player()
{
    mTexture = NULL;
    mPosX = 0;
    mPosY = 0;
    mWidth = 0;
    mHeight = 0;
    mPlayerSpeed = 0;
}
Player::Player(int startX, int startY, int width, int height)
{
    mTexture = NULL;
    mPosX = startX;
    mPosY = startY;
    mWidth = width;
    mHeight = height;
    mPlayerSpeed = 10; // TODO - make a better system
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
    mTexture = std::make_unique<Texture>();
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
            mVelY -= mPlayerSpeed;
            break;
        case SDLK_s:
            mVelY += mPlayerSpeed;
            break;
        case SDLK_a:
            mVelX -= mPlayerSpeed;
            break;
        case SDLK_d:
            mVelX += mPlayerSpeed;
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
            mVelY += mPlayerSpeed;
            break;
        case SDLK_s:
            mVelY -= mPlayerSpeed;
            break;
        case SDLK_a:
            mVelX += mPlayerSpeed;
            break;
        case SDLK_d:
            mVelX -= mPlayerSpeed;
            break;

        default:
            break;
        }
    }
}
void Player::render(std::unique_ptr<Window> &window)
{
    movePlayerSprite(window->getWidth(), window->getHeight());
    mTexture->render(window->getRenderer(), mPosX, mPosY);
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

void Player::movePlayerSprite(int windowWidth, int windowHeight)
{
    mPosX += mVelX;
    mPosY += mVelY;

    if (mPosX < 0)
    {
        mPosX = 0;
    }
    else if (mPosX + mWidth > windowWidth)
    {
        mPosX = windowWidth - mWidth;
    }

    if (mPosY < 0)
    {
        mPosY = 0;
    }
    else if (mPosY + mHeight > windowHeight)
    {
        mPosY = windowHeight - mHeight;
    }
}