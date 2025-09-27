#pragma once

#include "Window.h"
#include "Texture.h"

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
    void move(int &levelWidth, int &levelHeight);
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
    int mPosX, mPosY;
    int mVelX, mVelY;
    int mXMotion, mYMotion;
    int mWidth, mHeight;
    int mPlayerSpeedMAX;
    int mPlayerAcceleration;

    void updateVelocity();
    void updateXVelocity();
    void updateYVelocity();
    void updatePos(int &levelWidth, int &levelHeight);
};