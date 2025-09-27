#include "Game.h"

Game::Game()
{
    mIsrunning = false;
    mWindow = std::make_unique<Window>();
    mConfigFilePath = "conf/sizes.txt";
    int camX = 0;
    int camY = 0;
    mCamera = Camera();
    mLevel = Level();
    mBackgroundTex = std::make_unique<Texture>();
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
    mPlayer->move(mLevel.levelWidth, mLevel.levelHeight);
    mCamera.updatePosition(mWindow, mPlayer);
    mCamera.keepCameraInBounds(mLevel.levelWidth, mLevel.levelHeight, mWindow);
}
void Game::render()
{
    SDL_RenderClear(mWindow->getRenderer());
    mBackgroundTex->render(mWindow->getRenderer(), -mCamera.camX, -mCamera.camY);
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
    std::string stringValue;
    int intValue1 = 0;
    int intValue2 = 0;

    printInfo(logLevel, messageDepth, "Opening configuration file...\n");
    (*messageDepth)++;
    std::ifstream file;
    file.open(mConfigFilePath, std::ifstream::in);

    intValue1 = getNextInt(file, stringValue);
    intValue2 = getNextInt(file, stringValue);
    if (!initWindow(logLevel, messageDepth, intValue1, intValue2))
    {
        return false;
    }

    intValue1 = getNextInt(file, stringValue); // Tile side length. TODO

    intValue1 = getNextInt(file, stringValue);
    intValue2 = getNextInt(file, stringValue);
    if (!loadPlayerAssets(logLevel, messageDepth, intValue1, intValue2))
    {
        return false;
    }

    mLevel.levelWidth = getNextInt(file, stringValue);
    mLevel.levelHeight = getNextInt(file, stringValue);

    if (!loadBackgroundTex(logLevel, messageDepth, mLevel.levelWidth, mLevel.levelHeight))
    {
        return false;
    }

    (*messageDepth)--;
    printInfo(logLevel, messageDepth, "Closing configuration file... ");
    file.close();
    printInfo(logLevel, messageDepth, "Success.\n");

    return true;
}
int Game::getNextInt(std::ifstream &inputFileStream, std::string &readIntoValue)
{
    std::getline(inputFileStream, readIntoValue);
    return stoi(readIntoValue);
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