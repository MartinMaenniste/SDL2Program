#pragma once

#include "Player.h"

struct Camera
{
    int camX = 0, camY = 0;
    int camWidth = 0, camHeight = 0;
    void keepCameraInBounds(int levelWidth, int levelHeight, std::unique_ptr<Window> &window);
    void updatePosition(std::unique_ptr<Window> &window, std::unique_ptr<Player> &player);
    SDL_Rect getCameraRect();
};
struct Level
{
    int levelWidth = 0, levelHeight = 0;
};

struct Tiles
{
    int tilesHorizontally = 0, tilesVertically = 0;
    int scale = 0;
    int sideLength = 0;
    std::vector<Tile> tiles;
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
    const char *mConfigFilePath = "conf/sizes.txt";
    const char *mBGTexPath = "./assets/background.png";
    const char *mTileSheetPath = "./assets/Tiles.png";
    const char *mMapPath = "conf/tilemap.txt";
    bool mIsrunning;
    std::unique_ptr<Window> mWindow;
    int mPreferredWindowWidth;
    int mPreferredWindowHeigh;
    std::unique_ptr<Player> mPlayer;
    Camera mCamera;
    Level mLevel;
    std::unique_ptr<Texture> mBackgroundTex;
    std::unique_ptr<Texture> mStylesheetTex;
    Tiles mTiles;

    bool makeClassVariables(int *logLevel, int *messageDepth);
    int getNextInt(std::ifstream &inputFileStream);
    bool initSDL(int *logLevel, int *messageDepth);
    bool initWindow(int *logLevel, int *messageDepth, int defaultWidth, int defaultHeight);
    bool loadPlayerAssets(int *logLevel, int *messageDepth, int playerWidth, int playerHeight);
    bool loadBackgroundTex(int *logLevel, int *messageDepth, int texWidth, int texHeight);
    bool loadTileStylesheet(int sideLength, int *logLevel, int *messageDepth);
    bool loadTiles(int *logLevel, int *messageDepth);
    void addTileByType(int tileType, int indexInVector, int posX, int posY);
    void renderTiles();
};