#include "Window.h"
#include "globalFunctions.h"

class Game
{
public:
    Game();
    ~Game();

    bool init(int *logLevel, int *messageDepth);
    bool loadMedia(int *logLevel, int *messageDepth);
    void start();
    void close(int *logLevel, int *messageDepth);
    bool isRunning();
    void quitPressed();

private:
    std::unique_ptr<Window> mWindow;
    bool mIsrunning;
    int mPreferredWindowWidth;
    int mPreferredWindowHeigh;
};