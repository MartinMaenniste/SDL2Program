#include "globalFunctions.h"

class Window
{
public:
    Window();
    ~Window();

    bool init(int *logLevel, int *messageDepth);
    void close();

private:
    SDL_Window *mWindow;
    SDL_Surface *mScreenSurface;
    int mWindowWidth;
    int mWindowHeight;
};
