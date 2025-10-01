#pragma once

#include "Window.h"
#include "Texture.h"
#include "Tile.h"

class Window;
class Texture;

class Player
{
public:
    Player();
    Player(int startX, int startY, int width, int height);
    ~Player();

    bool loadAssets(SDL_Renderer *renderer, int *logLevel, int *messageDepth);
    void handleEvents(SDL_Event &event);
    void move(int &levelWidth, int &levelHeight, const std::vector<Tile> &tiles, int tileTexSize);
    void render(std::unique_ptr<Window> &window, int cameraX, int cameraY);
    void close(int *logLevel, int *messageDepth);
    int getXPosition();
    int getYPosition();
    int getWidth();
    int getHeight();
    void setXPosition(int xPosition);
    void setYPosition(int yPosition);

private:
    std::unique_ptr<Texture> mTexture;
    const char *mImagePath = "./assets/Player2.png";
    SDL_Rect mHitbox;
    int mVelX, mVelY;
    int mXMotion, mYMotion;
    int mPlayerSpeedMAX;
    int mPlayerAcceleration;

    void updateVelocity();
    void updateXVelocity();
    void updateYVelocity();
    int acceleratePlayer(int velocity, int direction);
    int deceleratePlayer(int velocity);
    void updatePos(int &levelWidth, int &levelHeight, const std::vector<Tile> &tiles);
    void correctForLevel(int &levelWidth, int &levelHeight);
    void correctForTilesX(const std::vector<Tile> &tiles);
    void correctForTilesY(const std::vector<Tile> &tiles);
};