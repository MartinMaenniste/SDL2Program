#include "Game.h"
#include "Window.h"
#include "Player.h"
#include "Texture.h"
#include "OnGroundItemHandler.h"

Game::Game()
{
    mIsrunning = false;
    mWindow = std::make_unique<Window>();
    int camX = 0;
    int camY = 0;
    mCamera = Camera();
    mLevel = Level();
    mTiles = Tiles();
    mTileStylesheetTex = std::make_unique<Texture>();
    mItemHandler = std::make_unique<OnGroundItemHandler>();
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
void Game::handleEvents(const SDL_Event &event)
{
    if (event.type == SDL_QUIT)
    {
        mIsrunning = false;
        return;
    }
    /*if (event.type == SDL_MOUSEBUTTONDOWN)
    {

         else
         {
             std::unique_ptr<Item> item = mUI.removeItemFomInventory(0);
             // No class to handle making it back to ongrounditem so we do it here.
             item->setX(mPlayer->getXPosition() + (mPlayer->getWidth() - item->getSidelength()) / 2);
             item->setY(mPlayer->getYPosition() + (mPlayer->getHeight() - item->getSidelength()));

             mOnGroundItems.push_back(std::move(item));
         }
    }*/

    mPlayer->handleEvents(event, mItemHandler);
    mItemHandler->handleEvent(event, *mPlayer, mCamera.cameraRect);
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
    renderTiles();
    mItemHandler->render(mWindow->getRenderer(), mCamera.cameraRect);
    mPlayer->render(mWindow->getRenderer(), mCamera.cameraRect.x, mCamera.cameraRect.y);
    SDL_RenderPresent(mWindow->getRenderer());
}

void Game::close(int *logLevel, int *messageDepth)
{
    Global::printInfo(logLevel, messageDepth, "Quitting SDL...\n");
    SDL_Quit();
    Global::printInfo(logLevel, messageDepth, "Success.\n");
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

bool Game::makeClassVariables(const int *const logLevel, int *const messageDepth)
{
    int intValue1 = 0;
    int intValue2 = 0;

    Global::printInfo(logLevel, messageDepth, "Opening configuration file...\n");
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
    mCamera.cameraRect.w = intValue1;
    mCamera.cameraRect.h = intValue2;

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

    /*if (!loadBackgroundTex(logLevel, messageDepth, mLevel.levelWidth, mLevel.levelHeight))
    {
        return false;
    }*/

    // Before exiting, we can do tiles since Level is now initialised.
    if (!loadTiles(logLevel, messageDepth))
        return false;

    /*(*messageDepth)++;
    Global::printInfo(logLevel, messageDepth, "Loading UI...\n");
    if (!mUI.initialise(mWindow->getRenderer(), logLevel, messageDepth, mWindow->getWidth(), mWindow->getHeight()))
        return false;
    (*messageDepth)--;*/

    (*messageDepth)--;
    Global::printInfo(logLevel, messageDepth, "Closing configuration file... ");
    file.close();
    Global::printInfo(logLevel, messageDepth, "Success.\n");

    mItemHandler->addNewItemOnGround(logLevel, messageDepth, mWindow->getRenderer(), 2300, 1200);
    mItemHandler->addNewItemOnGround(logLevel, messageDepth, mWindow->getRenderer(), 2300, 1200);
    mItemHandler->addNewItemOnGround(logLevel, messageDepth, mWindow->getRenderer(), 2300, 1200);
    mItemHandler->addNewItemOnGround(logLevel, messageDepth, mWindow->getRenderer(), 2300, 1200);
    mItemHandler->addNewItemOnGround(logLevel, messageDepth, mWindow->getRenderer(), 2300, 1200);
    mItemHandler->addNewItemOnGround(logLevel, messageDepth, mWindow->getRenderer(), 2300, 1200);
    mItemHandler->addNewItemOnGround(logLevel, messageDepth, mWindow->getRenderer(), 2300, 1200);
    mItemHandler->addNewItemOnGround(logLevel, messageDepth, mWindow->getRenderer(), 2300, 1200);
    mItemHandler->addNewItemOnGround(logLevel, messageDepth, mWindow->getRenderer(), 2300, 1200);
    mItemHandler->addNewItemOnGround(logLevel, messageDepth, mWindow->getRenderer(), 2300, 1200);
    mItemHandler->addNewItemOnGround(logLevel, messageDepth, mWindow->getRenderer(), 2300, 1200);
    mItemHandler->addNewItemOnGround(logLevel, messageDepth, mWindow->getRenderer(), 2300, 1200);
    mItemHandler->addNewItemOnGround(logLevel, messageDepth, mWindow->getRenderer(), 2300, 1200);
    mItemHandler->addNewItemOnGround(logLevel, messageDepth, mWindow->getRenderer(), 2300, 1200);
    mItemHandler->addNewItemOnGround(logLevel, messageDepth, mWindow->getRenderer(), 2300, 1200);
    mItemHandler->addNewItemOnGround(logLevel, messageDepth, mWindow->getRenderer(), 2300, 1200);
    mItemHandler->addNewItemOnGround(logLevel, messageDepth, mWindow->getRenderer(), 2300, 1200);
    mItemHandler->addNewItemOnGround(logLevel, messageDepth, mWindow->getRenderer(), 2300, 1200);
    mItemHandler->addNewItemOnGround(logLevel, messageDepth, mWindow->getRenderer(), 2300, 1200);
    mItemHandler->addNewItemOnGround(logLevel, messageDepth, mWindow->getRenderer(), 2300, 1200);
    mItemHandler->addNewItemOnGround(logLevel, messageDepth, mWindow->getRenderer(), 2300, 1200);
    mItemHandler->addNewItemOnGround(logLevel, messageDepth, mWindow->getRenderer(), 2300, 1200);
    mItemHandler->addNewItemOnGround(logLevel, messageDepth, mWindow->getRenderer(), 2300, 1200);
    mItemHandler->addNewItemOnGround(logLevel, messageDepth, mWindow->getRenderer(), 2300, 1200);
    mItemHandler->addNewItemOnGround(logLevel, messageDepth, mWindow->getRenderer(), 2300, 1200);

    /*mItemHandler->addNewItemOnGround(logLevel, messageDepth, mWindow->getRenderer(), 2300, 900);
    mItemHandler->addNewItemOnGround(logLevel, messageDepth, mWindow->getRenderer(), 2300, 1000);
    mItemHandler->addNewItemOnGround(logLevel, messageDepth, mWindow->getRenderer(), 2300, 1100);
    mItemHandler->addNewItemOnGround(logLevel, messageDepth, mWindow->getRenderer(), 2300, 1200);
    mItemHandler->addNewItemOnGround(logLevel, messageDepth, mWindow->getRenderer(), 2300, 1300);
    mItemHandler->addNewItemOnGround(logLevel, messageDepth, mWindow->getRenderer(), 2300, 1400);
    mItemHandler->addNewItemOnGround(logLevel, messageDepth, mWindow->getRenderer(), 2300, 1500);
    mItemHandler->addNewItemOnGround(logLevel, messageDepth, mWindow->getRenderer(), 2300, 1600);*/


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
bool Game::initSDL(const int *const logLevel, int *const messageDepth)
{
    Global::printInfo(logLevel, messageDepth, "Initialising SDL...\n");
    (*messageDepth)++;
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        Global::printDebug(logLevel, messageDepth, "Could not initialise SDL: ");
        if ((*logLevel) > 0)
        {
            printf("%s\n", SDL_GetError());
        }
        return false;
    }
    Global::printInfo(logLevel, messageDepth, "SDL video initialised.\n");
    (*messageDepth)--;
    Global::printInfo(logLevel, messageDepth, "SDL initialised.\n");

    return true;
}
bool Game::initWindow(const int *const logLevel, int *const messageDepth, const int defaultWidth, const int defaultHeight)
{
    Global::printInfo(logLevel, messageDepth, "Initialising window.\n");
    (*messageDepth)++;
    if (!mWindow->init(logLevel, messageDepth, defaultWidth, defaultHeight))
    {
        Global::printDebug(logLevel, messageDepth, "Failed to initialise window.\n");
        return false;
    }
    (*messageDepth)--;
    Global::printInfo(logLevel, messageDepth, "Window initialised.\n");

    return true;
}
bool Game::loadPlayerAssets(const int *const logLevel, int *const messageDepth, const int playerWidth, const int playerHeight)
{
    Global::printInfo(logLevel, messageDepth, "Loading Player class assets...\n");
    (*messageDepth)++;

    mPlayer = std::make_unique<Player>((mLevel.levelWidth - playerWidth) / 2, (mLevel.levelHeight - playerHeight) / 2, playerWidth, playerHeight);
    mPlayer->loadAssets(mWindow->getRenderer(), logLevel, messageDepth, mWindow->getWidth(), mWindow->getHeight(), 50); // TODO - Remove magic numbers!!

    (*messageDepth)--;
    Global::printInfo(logLevel, messageDepth, "Player class assets made.\n");
    return true;
}
bool Game::loadTileStylesheet(const int sideLength, const int *const logLevel, int *const messageDepth)
{
    Global::printInfo(logLevel, messageDepth, "Loading tiles stylesheet...\n");
    (*messageDepth)++;
    if (!mTileStylesheetTex->loadTextureFromPath(mTileSheetPath, mWindow->getRenderer(), sideLength, sideLength, logLevel, messageDepth))
    {
        Global::printDebug(logLevel, messageDepth, "Failed to load stylesheet for tiles.\n");
        return false;
    }
    (*messageDepth)--;
    Global::printInfo(logLevel, messageDepth, "Tile stylesheet loaded.\n");
    return true;
}
bool Game::loadTiles(const int *const logLevel, int *const messageDepth)
{
    mTiles.tilesHorizontally = mLevel.levelWidth / (mTiles.sideLength * mTiles.scale);
    mTiles.tilesVertically = mLevel.levelHeight / (mTiles.sideLength * mTiles.scale);

    Global::printInfo(logLevel, messageDepth, "Loading tiles...\n");
    (*messageDepth)++;

    Global::printInfo(logLevel, messageDepth, "Opening map file for tiles...\n");
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
    Global::printInfo(logLevel, messageDepth, "Closing map file for tiles.\n");
    file.close();

    (*messageDepth)--;
    Global::printInfo(logLevel, messageDepth, "Tiles loaded.\n");

    return true;
}
void Game::renderTiles()
{
    for (Tile t : mTiles.tiles)
    {
        t.render(mWindow->getRenderer(), mCamera.cameraRect, mTileStylesheetTex, mTiles.scale);
    }
}
void Game::addTileByType(const int tileType, const int indexInVector, const int posX, const int posY)
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
    if (cameraRect.x < 0)
    {
        cameraRect.x = 0;
    }
    if (cameraRect.y < 0)
    {
        cameraRect.y = 0;
    }
    if (cameraRect.x > levelWidth - window->getWidth())
    {
        cameraRect.x = levelWidth - window->getWidth();
    }
    if (cameraRect.y > levelHeight - window->getHeight())
    {
        cameraRect.y = levelHeight - window->getHeight();
    }
}
void Camera::updatePosition(std::unique_ptr<Window> &window, std::unique_ptr<Player> &player)
{
    cameraRect.x = player->getXPosition() + player->getWidth() / 2 - window->getWidth() / 2;
    cameraRect.y = player->getYPosition() + player->getHeight() / 2 - window->getHeight() / 2;
}
