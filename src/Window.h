#pragma once

#include "GlobalFunctions.h"

class Window
{
public:
    Window();
    ~Window();

    bool init(int *logLevel, int *messageDepth, int defaultWindowWidth, int defaultWindowHeight);
    void close(int *logLevel, int *messageDepth);
    SDL_Renderer *getRenderer();
    int getWidth();
    int getHeight();

private:
    SDL_Window *mWindow;
    SDL_Renderer *mRenderer;
    int mWindowWidth, mWindowHeight;

    bool createWindow(int *logLevel, int *messageDepth);
    bool createRenderer(int *logLevel, int *messageDepth);
    bool initialisePNGLoading(int *logLevel, int *messageDepth);
};
