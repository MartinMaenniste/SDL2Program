#include "Game.h"

Game::Game()
{
    mIsrunning = false;
    mWindow = std::make_unique<Window>();
}
Game::~Game()
{
}
bool Game::init(int *logLevel, int *messageDepth) // Basically make a functioning window on the screen.
{

    if (!initSDL(logLevel, messageDepth))
    {
        return false;
    }

    if (!initWindow(logLevel, messageDepth))
    {
        return false;
    }

    return true;
}
bool Game::loadAssets(int *logLevel, int *messageDepth)
{
    if (!loadPlayerAssets(logLevel, messageDepth))
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
void Game::render()
{
    SDL_RenderClear(mWindow->getRenderer());
    mPlayer->render(mWindow);
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
bool Game::initWindow(int *logLevel, int *messageDepth)
{
    printInfo(logLevel, messageDepth, "Initialising window.\n");
    (*messageDepth)++;
    if (!mWindow->init(logLevel, messageDepth))
    {
        printDebug(logLevel, messageDepth, "Failed to initialise window.\n");
        return false;
    }
    (*messageDepth)--;
    printInfo(logLevel, messageDepth, "Window initialised.\n");

    return true;
}
bool Game::loadPlayerAssets(int *logLevel, int *messageDepth)
{
    printInfo(logLevel, messageDepth, "Loading Player class assets...\n");
    (*messageDepth)++;

    mPlayer = std::make_unique<Player>(mWindow->getWidth() / 2 - 25, mWindow->getHeight() / 2 - 25, 50, 50);
    mPlayer->loadAssets(mWindow->getRenderer(), logLevel, messageDepth);

    (*messageDepth)--;
    printInfo(logLevel, messageDepth, "Player class assets made.\n");
    return true;
}