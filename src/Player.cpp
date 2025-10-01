#include "Player.h"

Player::Player()
{
    mTexture = NULL;
    mPlayerSpeedMAX = 0;
    mPlayerAcceleration = 0;
    mTexture = std::make_unique<Texture>();
    mHitbox = {0, 0, 0, 0};
}
Player::Player(int startX, int startY, int width, int height)
{
    mTexture = NULL;
    mHitbox = {startX, startY, width, height};
    mPlayerSpeedMAX = 10; // TODO - make a better system
    mPlayerAcceleration = 1;
    mVelX = 0;
    mVelY = 0;
    mXMotion = 0;
    mYMotion = 0;
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
    mTexture->loadTextureFromSurface(mImagePath, imageSurface, renderer, mHitbox.w, mHitbox.h, logLevel, messageDepth);
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
void Player::move(int &levelWidth, int &levelHeight, const std::vector<Tile> &tiles, int tileTexSize)
{
    updateVelocity();
    updatePos(levelWidth, levelHeight, tiles);
}
void Player::render(std::unique_ptr<Window> &window, int cameraX, int cameraY)
{
    mTexture->render(window->getRenderer(), mHitbox.x - cameraX, mHitbox.y - cameraY);
}
void Player::close(int *logLevel, int *messageDepth)
{
    printInfo(logLevel, messageDepth, "Closing player...\n");
    (*messageDepth)++;
    mTexture->close(logLevel, messageDepth);
    (*messageDepth)--;
    printInfo(logLevel, messageDepth, "Player closed.\n");
}
int Player::getXPosition() { return mHitbox.x; }
int Player::getYPosition() { return mHitbox.y; }
int Player::getWidth() { return mHitbox.w; }
int Player::getHeight() { return mHitbox.h; }

void Player::updateVelocity()
{
    updateXVelocity();
    updateYVelocity();
}
void Player::updateXVelocity()
{

    if (mXMotion == 0)
    {
        // If the player should be stationary, slow player down.
        mVelX = deceleratePlayer(mVelX);
    }
    else
    {
        // Otherwise speed up, player should be moving in mXMotion's direction
        mVelX = acceleratePlayer(mVelX, mXMotion);
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
        mVelY = deceleratePlayer(mVelY);
    }
    else
    {
        // Otherwise speed up, player should be moving in mYMotion's direction
        mVelY = acceleratePlayer(mVelY, mYMotion);
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
int Player::acceleratePlayer(int velocity, int direction)
{
    velocity += direction * mPlayerAcceleration;
    return velocity;
}
int Player::deceleratePlayer(int velocity)
{
    if (abs(velocity) == 1 || abs(velocity) == 0) // If player is moving only slightly, stop. If already stopped, keep the velocity at 0
        velocity = 0;
    else
        velocity > 0 ? velocity -= mPlayerAcceleration : velocity += mPlayerAcceleration;

    return velocity;
}
void Player::updatePos(int &levelWidth, int &levelHeight, const std::vector<Tile> &tiles)
{
    // Check if moving x makes a collision with tiles, check if moving y makes a collision with tiles.
    // For both of them, snap to the tile, then skip (or recursion if there is an odd case.)
    // After that, correctforlevel.

    mHitbox.x += mVelX;
    correctForTilesX(tiles);
    mHitbox.y += mVelY;
    correctForTilesY(tiles);

    correctForLevel(levelWidth, levelHeight);
}
void Player::correctForLevel(int &levelWidth, int &levelHeight)
{
    if (mHitbox.x < 0)
    {
        mHitbox.x = 0;
    }
    else if (mHitbox.x + mHitbox.w > levelWidth)
    {
        mHitbox.x = levelWidth - mHitbox.w;
    }

    if (mHitbox.y < 0)
    {
        mHitbox.y = 0;
    }
    else if (mHitbox.y + mHitbox.h > levelHeight)
    {
        mHitbox.y = levelHeight - mHitbox.h;
    }
}
void Player::correctForTilesX(const std::vector<Tile> &tiles)
{
    SDL_Rect tileHB;
    for (Tile t : tiles)
    {
        if (t.getWalkThrough())
            continue;

        tileHB = t.getHitbox();
        if (!areColliding(mHitbox, tileHB))
            continue;

        if (mVelX > 0)
            mHitbox.x = tileHB.x - mHitbox.w;

        else if (mVelX < 0)
            mHitbox.x = tileHB.x + tileHB.w;

        mVelX = 0;
        return;
    }
}
void Player::correctForTilesY(const std::vector<Tile> &tiles)
{
    SDL_Rect tileHB;
    for (Tile t : tiles)
    {
        if (t.getWalkThrough())
            continue;

        tileHB = t.getHitbox();
        if (!areColliding(mHitbox, tileHB))
            continue;

        if (mVelY > 0)
            mHitbox.y = tileHB.y - mHitbox.h;

        else if (mVelY < 0)
            mHitbox.y = tileHB.y + tileHB.h;

        mVelY = 0;
        return;
    }
}