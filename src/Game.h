#pragma once

#include "GlobalFunctions.h"

class Window;
class Tile;
class Player;
class Texture;
class OnGroundItemHandler;

struct Camera
{
    SDL_Rect cameraRect = {0, 0, 0, 0};
    void keepCameraInBounds(int levelWidth, int levelHeight, std::unique_ptr<Window> &window);
    void updatePosition(std::unique_ptr<Window> &window, std::unique_ptr<Player> &player);
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
public:      //                             Game controlls interactions between classes that know nothing about eachother. vector for all items in the world
    Game();  //                             Pop the items that are in inventory or chests, those objects handle them. If they are dropped, they are returned.
    ~Game(); //             That is handled via handleEvents that will get very complicated. (class functions probably want some container reference as input
             //             to put stuff into that are deleted from that class).
    bool init(int *logLevel, int *messageDepth);
    void start();
    void handleEvents(const SDL_Event &event);
    void updatePositions();
    void render();
    void close(int *logLevel, int *messageDepth);
    bool isRunning();
    void quitPressed();

private:
    const char *mConfigFilePath = "conf/sizes.txt";
    const char *mTileSheetPath = "./assets/Tiles.png";
    const char *mMapPath = "conf/tilemap.txt";
    bool mIsrunning;
    std::unique_ptr<Window> mWindow;
    int mPreferredWindowWidth;
    int mPreferredWindowHeigh;
    std::unique_ptr<Player> mPlayer;
    Camera mCamera;
    Level mLevel;
    std::unique_ptr<Texture> mStylesheetTex;
    Tiles mTiles;
    std::unique_ptr<OnGroundItemHandler> mItemHandler;

    bool makeClassVariables(const int *const logLevel, int *const messageDepth);
    int getNextInt(std::ifstream &inputFileStream);
    bool initSDL(const int *const logLevel, int *const messageDepth);
    bool initWindow(const int *const logLevel, int *const messageDepth, const int defaultWidth, const int defaultHeight);
    bool loadPlayerAssets(const int *const logLevel, int *const messageDepth, const int playerWidth, const int playerHeight);
    bool loadTileStylesheet(const int sideLength, const int *const logLevel, int *const messageDepth);
    bool loadTiles(const int *const logLevel, int *const messageDepth);
    void addTileByType(const int tileType, const int indexInVector, const int posX, const int posY);
    void renderTiles();
};