#include "Game.h"

int main()
{
    Game game = Game();
    int messageDepth = 0;
    int logLevel = 2; // 0 - show nothing; 1 - show debug (errors); 2 - show debug + general info about what is currently going on

    printInfo(&logLevel, &messageDepth, "Initialising program...\n");
    messageDepth++;
    if (!game.init(&logLevel, &messageDepth))
    {
        printDebug(&logLevel, &messageDepth, "Failed to init!\nQuitting program.\n");

        return 0;
    }
    messageDepth--;
    printInfo(&logLevel, &messageDepth, "Program initialised.\n");

    printInfo(&logLevel, &messageDepth, "Loading media...\n");
    messageDepth++;
    if (!game.loadAssets(&logLevel, &messageDepth))
    {
        printDebug(&logLevel, &messageDepth, "Failed to load media!\nQuitting program.\n");
        return 0;
    }
    messageDepth--;
    printInfo(&logLevel, &messageDepth, "Media loaded.\n");

    game.start();
    printInfo(&logLevel, &messageDepth, "Game started!\n");
    while (game.isRunning())
    {

        SDL_Event e;
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
            {
                game.quitPressed();
            }
        }
        game.render();
    }
    printDebug(&logLevel, &messageDepth, "Quitting program...\n"); // If program didn't crash, but something ended game loop unexpectedly - debug rather than just info
    messageDepth++;
    game.close(&logLevel, &messageDepth);
    messageDepth--;

    printf("Goodbye.\n");
    return 0;
}