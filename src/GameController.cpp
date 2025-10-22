#include "GameController.h"

GameController::GameController()
{
    Game mGame = Game();
    mMessageDepth = 0;
    mLogLevel = 0;
}
GameController::GameController(char *logLevel)
{
    Game mGame = Game();
    mMessageDepth = 0;
    mLogLevel = std::atoi(logLevel);
}
GameController::~GameController()
{
}
void GameController::startApplication()
{
    if (!initGame())
        return;
    startGame();
    closeGame();
}

bool GameController::initGame()
{
    Global::printInfo(&mLogLevel, &mMessageDepth, "Initialising program...\n");
    mMessageDepth++;
    if (!mGame.init(&mLogLevel, &mMessageDepth))
    {
        Global::printDebug(&mLogLevel, &mMessageDepth, "Failed to init!\nQuitting program.\n");

        return false;
    }
    mMessageDepth--;
    Global::printInfo(&mLogLevel, &mMessageDepth, "Program initialised.\n");
    return true;
}
void GameController::startGame()
{
    mGame.start(); // This only sets the Game class internally to a state where it tells that it's running. (isRunning is set to true)
    Global::printInfo(&mLogLevel, &mMessageDepth, "Game started!\n");

    Uint64 frameStartTime = 0;
    Uint64 frameEndTime = 0;

    Uint64 millisToWait = 0;

    Uint64 runningTime = 0;
    Uint64 beforeLoopTime = SDL_GetTicks64();

    Uint64 totalFrames = 0;
    int framerate = 60;
    int averageFPS = 0;
    int millisPerFrame = 1000 / framerate;

    while (mGame.isRunning())
    {
        frameStartTime = SDL_GetTicks64();

        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            mGame.handleEvents(event);
        }
        mGame.updatePositions();
        mGame.render();

        frameEndTime = SDL_GetTicks64();
        runningTime = frameEndTime - beforeLoopTime;
        millisToWait = millisPerFrame - (frameEndTime - frameStartTime);
        if (millisToWait > 0)
        {
            SDL_Delay(millisToWait);
        }
        totalFrames++;
        averageFPS = totalFrames / (runningTime / 1000.0f);
        // No font system made yet, can't yet display fps.
    }
}
void GameController::closeGame()
{
    Global::printDebug(&mLogLevel, &mMessageDepth, "Quitting program...\n"); // If program didn't crash, but something ended game loop unexpectedly - debug rather than just info
    mMessageDepth++;
    mGame.close(&mLogLevel, &mMessageDepth);
    mMessageDepth--;

    printf("Goodbye.\n");
}
