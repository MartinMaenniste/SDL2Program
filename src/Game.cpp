#include "Game.h"

Game::Game()
{
    mIsrunning = true;
    mWindow = std::make_unique<Window>();
}
Game::~Game()
{
}
bool Game::init(int *logLevel, int *messageDepth)
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
    printInfo(logLevel, messageDepth, "Video initialised.\n");
    (*messageDepth)--;
    printInfo(logLevel, messageDepth, "SDL initialised.\n");

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
bool Game::loadMedia(int *logLevel, int *messageDepth)
{
    return true;
}
void Game::start()
{
}
void Game::close(int *logLevel, int *messageDepth)
{
    printInfo(logLevel, messageDepth, "Quitting SDL...\n");
    SDL_Quit();
    printInfo(logLevel, messageDepth, "Success.\n");

    printDebug(logLevel, messageDepth, "Destroying application window...\n");
    mWindow->close();
    printInfo(logLevel, messageDepth, "Success.\n");
}
bool Game::isRunning()
{
    return mIsrunning;
}
void Game::quitPressed()
{
    mIsrunning = false;
}