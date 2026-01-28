#include "Player.h"
#include "Inventory.h"
#include "Interactable.h"

Player::Player()
{
    mTexture = NULL;
    mPlayerSpeedMAX = 0;
    mPlayerAcceleration = 0;
    mTexture = std::make_unique<Texture>();
    mInventory = std::make_unique<Inventory>();
    mHitbox = {0, 0, 0, 0};
}
Player::Player(const int startX, const int startY, const int width, const int height)
{
    mTexture = NULL;
    mHitbox = {startX, startY, width, height};
    mPlayerSpeedMAX = 7; // TODO - make a better system
    mPlayerAcceleration = 1;
    mVelX = 0;
    mVelY = 0;
    mXMotion = 0;
    mYMotion = 0;
    mTexture = std::make_unique<Texture>();
    mInventory = std::make_unique<Inventory>();
}
Player::~Player()
{
}
bool Player::loadAssets(SDL_Renderer *renderer, const int *logLevel, int *messageDepth, const int windowWidth, const int windowHeight, const int maxInvSlots)
{
    Global::printInfo(logLevel, messageDepth, "Initialising player...\n");
    (*messageDepth)++;
    mTexture->loadTexture(mImagePath, renderer, mHitbox.w, mHitbox.h, logLevel, messageDepth);

    Global::printInfo(logLevel, messageDepth, "Making inventory for player...\n");
    mInventory->init(renderer, windowWidth, windowHeight, logLevel, messageDepth, maxInvSlots);
    Global::printInfo(logLevel, messageDepth, "Inventory created.\n");

    Global::printInfo(logLevel, messageDepth, "Player initialised.\n");
    return true;
}
void Player::handleEvents(const SDL_Event &event, std::unique_ptr<OnGroundItemHandler> &groundItems)
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
    mInventory->handleEvent(event, groundItems, mHitbox);
}
void Player::move(const int &levelWidth, const int &levelHeight, const std::vector<Tile> &tiles, const int tileTexSize, const std::vector<std::unique_ptr<Interactable>> &interactables)
{
    updateVelocity();
    updatePos(levelWidth, levelHeight, tiles, interactables);
}
void Player::render(SDL_Renderer *renderer, const int cameraX, const int cameraY)
{
    mTexture->render(renderer, mHitbox.x - cameraX, mHitbox.y - cameraY);
    mInventory->render(renderer);
}
void Player::close(const int *logLevel, int *messageDepth)
{
    Global::printInfo(logLevel, messageDepth, "Closing player...\n");
    (*messageDepth)++;
    mTexture->close(logLevel, messageDepth);
    (*messageDepth)--;
    Global::printInfo(logLevel, messageDepth, "Player closed.\n");
}
int Player::getXPosition() { return mHitbox.x; }
int Player::getYPosition() { return mHitbox.y; }
int Player::getWidth() { return mHitbox.w; }
int Player::getHeight() { return mHitbox.h; }
SDL_Rect Player::getHitbox() { return mHitbox; }

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
int Player::acceleratePlayer(int velocity, const int direction)
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
void Player::updatePos(const int &levelWidth, const int &levelHeight, const std::vector<Tile> &tiles, const std::vector<std::unique_ptr<Interactable>> &interactables)
{
    // Check if moving x makes a collision with tiles, check if moving y makes a collision with tiles.
    // For both of them, snap to the tile, then skip (or recursion if there is an odd case.)
    // After that, correctforlevel.

    mHitbox.x += mVelX;
    correctForImmovablesX(tiles, interactables);
    mHitbox.y += mVelY;
    correctForImmovablesY(tiles, interactables);

    correctForLevel(levelWidth, levelHeight);
}
void Player::correctForLevel(const int &levelWidth, const int &levelHeight)
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
void Player::correctForImmovablesX(const std::vector<Tile> &tiles, const std::vector<std::unique_ptr<Interactable>> &interactables)
{
    SDL_Rect tileHB;
    for (Tile t : tiles)
    {
        if (t.getWalkThrough())
            continue;

        tileHB = t.getHitbox();
        if (!Global::areColliding(mHitbox, tileHB))
            continue;

        if (mVelX > 0)
            mHitbox.x = tileHB.x - mHitbox.w;

        else if (mVelX < 0)
            mHitbox.x = tileHB.x + tileHB.w;

        mVelX = 0;
        return;
    }
    SDL_Rect immovableHB;
    for (auto iter = interactables.begin(); iter != interactables.end(); iter++)
    {
        if((*iter)->getCanWalkThrough())
            continue;
        immovableHB = (*iter)->getHitbox();
        if (!Global::areColliding(mHitbox, immovableHB))
            continue;

        if (mVelX > 0)
            mHitbox.x = immovableHB.x - mHitbox.w;

        else if (mVelX < 0)
            mHitbox.x = immovableHB.x + immovableHB.w;

        mVelX = 0;
        return;
    }
}
void Player::correctForImmovablesY(const std::vector<Tile> &tiles, const std::vector<std::unique_ptr<Interactable>> &interactables)
{
    SDL_Rect tileHB;
    for (Tile t : tiles)
    {
        if (t.getWalkThrough())
            continue;

        tileHB = t.getHitbox();
        if (!Global::areColliding(mHitbox, tileHB))
            continue;

        if (mVelY > 0)
            mHitbox.y = tileHB.y - mHitbox.h;

        else if (mVelY < 0)
            mHitbox.y = tileHB.y + tileHB.h;

        mVelY = 0;
        return;
    }
    SDL_Rect immovableHB;
    for (auto iter = interactables.begin(); iter != interactables.end(); iter++)
    {
        if ((*iter)->getCanWalkThrough())
            continue;

        immovableHB = (*iter)->getHitbox();
        if (!Global::areColliding(mHitbox, immovableHB))
            continue;

        if (mVelY > 0)
            mHitbox.y = immovableHB.y - mHitbox.h;

        else if (mVelY < 0)
            mHitbox.y = immovableHB.y + immovableHB.h;

        mVelY = 0;
        return;
    }
}
void Player::addItemToInventory(std::unique_ptr<Item> &item)
{
    mInventory->addItem(item);
}