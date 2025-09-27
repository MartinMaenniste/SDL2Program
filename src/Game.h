#pragma once

#include "Player.h"

struct Camera
{
    int camX = 0, camY = 0;
    void keepCameraInBounds(int levelWidth, int levelHeight, std::unique_ptr<Window> &window);
    void updatePosition(std::unique_ptr<Window> &window, std::unique_ptr<Player> &player);
};
struct Level
{
    int levelWidth = 0, levelHeight = 0;
};

class Game
{
public:
    Game();
    ~Game();

    bool init(int *logLevel, int *messageDepth);
    void start();
    void handleEvents(SDL_Event &event);
    void updatePositions();
    void render();
    void close(int *logLevel, int *messageDepth);
    bool isRunning();
    void quitPressed();

private:
    const char *mConfigFilePath;
    bool mIsrunning;
    std::unique_ptr<Window> mWindow;
    int mPreferredWindowWidth;
    int mPreferredWindowHeigh;
    std::unique_ptr<Player> mPlayer;
    Camera mCamera;
    Level mLevel;
    std::unique_ptr<Texture> mBackgroundTex;
    const char *mBGTexPath = "./assets/background.png";

    bool makeClassVariables(int *logLevel, int *messageDepth);
    int getNextInt(std::ifstream &inputFileStream, std::string &readIntoValue);
    bool initSDL(int *logLevel, int *messageDepth);
    bool initWindow(int *logLevel, int *messageDepth, int defaultWidth, int defaultHeight);
    bool loadPlayerAssets(int *logLevel, int *messageDepth, int playerWidth, int playerHeight);
    bool loadBackgroundTex(int *logLevel, int *messageDepth, int texWidth, int texHeight);
};