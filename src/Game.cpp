#include "Game.h"

Game::Game()
{
    mIsrunning = false;
    mWindow = std::make_unique<Window>();
    int camX = 0;
    int camY = 0;
    mCamera = Camera();
    mLevel = Level();
    mTiles = Tiles();
    mBackgroundTex = std::make_unique<Texture>();
    mStylesheetTex = std::make_unique<Texture>();
}
Game::~Game()
{
}
bool Game::init(int *logLevel, int *messageDepth) // Initialises all the classes - handles the todo for classes before they can be made + makes them.
{
    if (!initSDL(logLevel, messageDepth))
    {
        return false;
    }

    if (!makeClassVariables(logLevel, messageDepth))
    {
        return false;
    }

    return true;
}
void Game::start()
{
    mIsrunning = true;
}
void Game::handleEvents(SDL_Event &event)
{
    if (event.type == SDL_QUIT)
    {
        mIsrunning = false;
    }
    mPlayer->handleEvents(event);
}
void Game::updatePositions()
{
    mPlayer->move(mLevel.levelWidth, mLevel.levelHeight, mTiles.tiles, mTiles.sideLength * mTiles.scale);
    mCamera.updatePosition(mWindow, mPlayer);
    mCamera.keepCameraInBounds(mLevel.levelWidth, mLevel.levelHeight, mWindow);
}
void Game::render()
{
    SDL_RenderClear(mWindow->getRenderer());
    mBackgroundTex->render(mWindow->getRenderer(), -mCamera.camX, -mCamera.camY);
    renderTiles();
    mPlayer->render(mWindow, mCamera.camX, mCamera.camY);
    SDL_RenderPresent(mWindow->getRenderer());
}

void Game::close(int *logLevel, int *messageDepth)
{
    printInfo(logLevel, messageDepth, "Quitting SDL...\n");
    SDL_Quit();
    printInfo(logLevel, messageDepth, "Success.\n");
    mWindow->close(logLevel, messageDepth);
    mPlayer->close(logLevel, messageDepth);
}
bool Game::isRunning()
{
    return mIsrunning;
}
void Game::quitPressed()
{
    mIsrunning = false;
}

bool Game::makeClassVariables(int *logLevel, int *messageDepth)
{
    int intValue1 = 0;
    int intValue2 = 0;

    printInfo(logLevel, messageDepth, "Opening configuration file...\n");
    (*messageDepth)++;
    std::ifstream file;
    file.open(mConfigFilePath, std::ifstream::in);

    // Level
    mLevel.levelWidth = getNextInt(file);
    mLevel.levelHeight = getNextInt(file);

    // Window
    intValue1 = getNextInt(file);
    intValue2 = getNextInt(file);
    if (!initWindow(logLevel, messageDepth, intValue1, intValue2))
    {
        return false;
    }
    mCamera.camWidth = intValue1;
    mCamera.camHeight = intValue2;

    // Tiles
    intValue1 = getNextInt(file);
    if (!loadTileStylesheet(intValue1, logLevel, messageDepth))
    {
        return false;
    }
    mTiles.sideLength = intValue1;
    mTiles.scale = getNextInt(file);
    // Tiles themselves need level to be done!

    // Player
    intValue1 = getNextInt(file);
    intValue2 = getNextInt(file);
    if (!loadPlayerAssets(logLevel, messageDepth, intValue1, intValue2))
    {
        return false;
    }

    if (!loadBackgroundTex(logLevel, messageDepth, mLevel.levelWidth, mLevel.levelHeight))
    {
        return false;
    }

    // Before exiting, we can do tiles since Level is now initialised.
    if (!loadTiles(logLevel, messageDepth))
        return false;

    (*messageDepth)--;
    printInfo(logLevel, messageDepth, "Closing configuration file... ");
    file.close();
    printInfo(logLevel, messageDepth, "Success.\n");

    return true;
}
int Game::getNextInt(std::ifstream &inputFileStream)
{
    // Reads integers from file seperated by space or newline, from left to right, up to down
    int value;
    if (!(inputFileStream >> value))
    {
        if (inputFileStream.eof())
        {
            // printf("\n\n***\nTried to read end of file!\n***\n\n\n"); // Tile loading waits until eof is reached, doesn't calculate or know how many there should be.
            return -1;
        }
        else
        {
            printf("\n\n***\nError trying to read next integer from file.\n***\n\n\n"); // Still print unknown error.
            return -1;
        }
    }

    return value;
}
bool Game::initSDL(int *logLevel, int *messageDepth)
{
    printInfo(logLevel, messageDepth, "Initialising SDL...\n");
    (*messageDepth)++;
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printDebug(logLevel, messageDepth, "Could not initialise SDL: ");
        if ((*logLevel) > 0)
        {
            printf("%s\n", SDL_GetError());
        }
        return false;
    }
    printInfo(logLevel, messageDepth, "SDL video initialised.\n");
    (*messageDepth)--;
    printInfo(logLevel, messageDepth, "SDL initialised.\n");

    return true;
}
bool Game::initWindow(int *logLevel, int *messageDepth, int defaultWidth, int defaultHeight)
{
    printInfo(logLevel, messageDepth, "Initialising window.\n");
    (*messageDepth)++;
    if (!mWindow->init(logLevel, messageDepth, defaultWidth, defaultHeight))
    {
        printDebug(logLevel, messageDepth, "Failed to initialise window.\n");
        return false;
    }
    (*messageDepth)--;
    printInfo(logLevel, messageDepth, "Window initialised.\n");

    return true;
}
bool Game::loadPlayerAssets(int *logLevel, int *messageDepth, int playerWidth, int playerHeight)
{
    printInfo(logLevel, messageDepth, "Loading Player class assets...\n");
    (*messageDepth)++;

    mPlayer = std::make_unique<Player>((mLevel.levelWidth - playerWidth) / 2, (mLevel.levelHeight - playerHeight) / 2, playerWidth, playerHeight);
    mPlayer->loadAssets(mWindow->getRenderer(), logLevel, messageDepth);

    (*messageDepth)--;
    printInfo(logLevel, messageDepth, "Player class assets made.\n");
    return true;
}
bool Game::loadBackgroundTex(int *logLevel, int *messageDepth, int texWidth, int texHeight)
{
    printInfo(logLevel, messageDepth, "Loading background texture...\n");

    if (!mBackgroundTex->loadTextureFromPath(mBGTexPath, mWindow->getRenderer(), texWidth, texHeight, logLevel, messageDepth))
    {
        printDebug(logLevel, messageDepth, "Failed to load background texture.\n");
        return false;
    }

    printInfo(logLevel, messageDepth, "Background texture loaded.\n");
    return true;
}
bool Game::loadTileStylesheet(int sideLength, int *logLevel, int *messageDepth)
{
    printInfo(logLevel, messageDepth, "Loading tiles stylesheet...\n");
    (*messageDepth)++;
    if (!mStylesheetTex->loadTextureFromPath(mTileSheetPath, mWindow->getRenderer(), sideLength, sideLength, logLevel, messageDepth))
    {
        printDebug(logLevel, messageDepth, "Failed to load stylesheet for tiles.\n");
        return false;
    }
    (*messageDepth)--;
    printInfo(logLevel, messageDepth, "Tile stylesheet loaded.\n");
    return true;
}
bool Game::loadTiles(int *logLevel, int *messageDepth)
{
    mTiles.tilesHorizontally = mLevel.levelWidth / (mTiles.sideLength * mTiles.scale);
    mTiles.tilesVertically = mLevel.levelHeight / (mTiles.sideLength * mTiles.scale);

    printInfo(logLevel, messageDepth, "Loading tiles...\n");
    (*messageDepth)++;

    printInfo(logLevel, messageDepth, "Opening map file for tiles...\n");
    (*messageDepth)++;

    std::ifstream file;
    file.open(mMapPath, std::ifstream::in);

    int xPos = 0, yPos = 0, tileType = 0, counter = 0;
    tileType = getNextInt(file);
    while (tileType != -1)
    {
        addTileByType(tileType, counter, xPos, yPos);

        xPos += mTiles.sideLength * mTiles.scale;
        if (xPos + (mTiles.sideLength * mTiles.scale) > mLevel.levelWidth)
        {
            xPos = 0;
            yPos += mTiles.sideLength * mTiles.scale;
        }

        tileType = getNextInt(file);
        counter++;
    }

    (*messageDepth)--;
    printInfo(logLevel, messageDepth, "Closing map file for tiles.\n");
    file.close();

    (*messageDepth)--;
    printInfo(logLevel, messageDepth, "Tiles loaded.\n");

    return true;
}
void Game::renderTiles()
{
    for (Tile t : mTiles.tiles)
    {
        t.render(mWindow->getRenderer(), mCamera.getCameraRect(), mStylesheetTex, mTiles.scale);
    }
}
void Game::addTileByType(int tileType, int indexInVector, int posX, int posY)
{
    mTiles.tiles.push_back(Tile());
    int stylesheetX = 0, stylesheetY = 0, sideLength = mTiles.sideLength;
    bool canWalkthrough = true;

    if (tileType == 0)
    {
        // Default values are perfect.
    }
    else if (tileType == 1)
    {
        canWalkthrough = false;
        stylesheetY += mTiles.sideLength + 1;
    }
    else
    {
        printf("Unknown tile type: %d\n", tileType);
        throw -1;
    }

    mTiles.tiles[indexInVector].setValues(stylesheetX, stylesheetY, sideLength, canWalkthrough, posX, posY, mTiles.scale);
}

void Camera::keepCameraInBounds(int levelWidth, int levelHeight, std::unique_ptr<Window> &window)
{
    if (camX < 0)
    {
        camX = 0;
    }
    if (camY < 0)
    {
        camY = 0;
    }
    if (camX > levelWidth - window->getWidth())
    {
        camX = levelWidth - window->getWidth();
    }
    if (camY > levelHeight - window->getHeight())
    {
        camY = levelHeight - window->getHeight();
    }
}
void Camera::updatePosition(std::unique_ptr<Window> &window, std::unique_ptr<Player> &player)
{
    camX = player->getXPosition() + player->getWidth() / 2 - window->getWidth() / 2;
    camY = player->getYPosition() + player->getHeight() / 2 - window->getHeight() / 2;
}
SDL_Rect Camera::getCameraRect()
{
    SDL_Rect returnable{this->camX, this->camY, this->camWidth, this->camHeight};
    return returnable;
}