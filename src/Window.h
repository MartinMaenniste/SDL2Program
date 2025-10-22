#pragma once

#include "GlobalFunctions.h"

class Window
{
public:
    Window();
    ~Window();

    bool init(const int *logLevel, int *messageDepth, const int defaultWindowWidth, const int defaultWindowHeight);
    void close(const int *logLevel, int *messageDepth);
    SDL_Renderer *getRenderer();
    int getWidth();
    int getHeight();

private:
    SDL_Window *mWindow;
    SDL_Renderer *mRenderer;
    int mWindowWidth, mWindowHeight;

    bool createWindow(const int *logLevel, int *messageDepth);
    bool createRenderer(const int *logLevel, int *messageDepth);
    bool initialisePNGLoading(const int *logLevel, int *messageDepth);
};
