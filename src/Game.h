#include "globalFunctions.h"
#include "Player.h"

class Game
{
public:
    Game();
    ~Game();

    bool init(int *logLevel, int *messageDepth);
    bool loadAssets(int *logLevel, int *messageDepth);
    void start();
    void handleEvents(SDL_Event &event);
    void render();
    void close(int *logLevel, int *messageDepth);
    bool isRunning();
    void quitPressed();

private:
    std::unique_ptr<Window> mWindow;
    bool mIsrunning;
    int mPreferredWindowWidth;
    int mPreferredWindowHeigh;
    std::unique_ptr<Player> mPlayer;

    bool initSDL(int *logLevel, int *messageDepth);
    bool initWindow(int *logLevel, int *messageDepth);
    bool loadPlayerAssets(int *logLevel, int *messageDepth);
};