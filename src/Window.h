#include "globalFunctions.h"

class Window
{
public:
    Window();
    Window(int width, int height);
    ~Window();

    bool init(int *logLevel, int *messageDepth);
    void close(int *logLevel, int *messageDepth);
    SDL_Renderer *getRenderer();
    int getWidth();
    int getHeight();

private:
    SDL_Window *mWindow;
    SDL_Renderer *mRenderer;
    int mWindowWidth;
    int mWindowHeight;

    void getWindowDimensions(int *logLevel, int *messageDepth);
    bool createWindow(int *logLevel, int *messageDepth);
    bool createRenderer(int *logLevel, int *messageDepth);
    bool initialisePNGLoading(int *logLevel, int *messageDepth);
};
