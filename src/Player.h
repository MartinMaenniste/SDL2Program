#pragma once

#include "Window.h"
#include "Tile.h"

class Inventory;
class OnGroundItemHandler;
class Item;

class Player
{
public:
    Player();
    Player(const int startX, const int startY, const int width, const int height);
    ~Player();

    bool loadAssets(SDL_Renderer *renderer, const int *logLevel, int *messageDepth, const int windowWidth, const int windowHeight, const int maxInvSlots);
    void handleEvents(const SDL_Event &event, std::unique_ptr<OnGroundItemHandler> &groundItems);
    void move(const int &levelWidth, const int &levelHeight, const std::vector<Tile> &tiles, const int tileTexSize);
    void render(SDL_Renderer *renderer, const int cameraX, const int cameraY);
    void close(const int *logLevel, int *messageDepth);
    int getXPosition();
    int getYPosition();
    int getWidth();
    int getHeight();
    SDL_Rect getHitbox();
    // void setXPosition(const int xPosition);
    // void setYPosition(const int yPosition);
    void addItemToInventory(std::unique_ptr<Item> &item);

private:
    std::unique_ptr<Texture> mTexture;
    const char *mImagePath = "./assets/Player2.png";
    SDL_Rect mHitbox;
    int mVelX, mVelY;
    int mXMotion, mYMotion;
    int mPlayerSpeedMAX;
    int mPlayerAcceleration;
    std::unique_ptr<Inventory> mInventory;

    void updateVelocity();
    void updateXVelocity();
    void updateYVelocity();
    int acceleratePlayer(int velocity, const int direction);
    int deceleratePlayer(int velocity);
    void updatePos(const int &levelWidth, const int &levelHeight, const std::vector<Tile> &tiles);
    void correctForLevel(const int &levelWidth, const int &levelHeight);
    void correctForTilesX(const std::vector<Tile> &tiles);
    void correctForTilesY(const std::vector<Tile> &tiles);
};