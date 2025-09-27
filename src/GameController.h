#pragma once

#include "Game.h"
#include "GlobalFunctions.h"

class GameController
{
public:
    GameController();
    GameController(char *logLevel);
    ~GameController();

    void startApplication();

private:
    Game mGame;
    int mMessageDepth; // To display a tree looking structure while initialising or closing the program.
    int mLogLevel;     // 0 - show nothing; 1 - show debug (errors); 2 - show debug + general info about what is currently going on

    bool initGame();
    bool loadAssets();
    void startGame();
    void closeGame();
};