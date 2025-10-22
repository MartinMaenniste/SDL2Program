#include "Window.h"

Window::Window()
{
    mWindow = NULL;
    mRenderer = NULL;
    mWindowWidth = 0;
    mWindowHeight = 0;
}
Window::~Window()
{
}
bool Window::init(const int *logLevel, int *messageDepth, const int defaultWindowWidth, const int defaultWindowHeight)
{
    mWindowWidth = defaultWindowWidth;
    mWindowHeight = defaultWindowHeight;

    if (!createWindow(logLevel, messageDepth))
    {
        return false;
    }

    if (!createRenderer(logLevel, messageDepth))
    {
        return false;
    }

    if (!initialisePNGLoading(logLevel, messageDepth))
    {
        return false;
    }

    return true;
}
void Window::close(const int *logLevel, int *messageDepth)
{
    Global::printInfo(logLevel, messageDepth, "Destroying renderer...\n");
    SDL_DestroyRenderer(mRenderer);
    Global::printInfo(logLevel, messageDepth, "Renderer destroyed.\n");
    Global::printInfo(logLevel, messageDepth, "Destroying window...\n");
    SDL_DestroyWindow(mWindow);
    Global::printInfo(logLevel, messageDepth, "Window destroyed.\n");
}
SDL_Renderer *Window::getRenderer() { return mRenderer; }
int Window::getWidth() { return mWindowWidth; }
int Window::getHeight() { return mWindowHeight; }

bool Window::createWindow(const int *logLevel, int *messageDepth)
{
    Global::printInfo(logLevel, messageDepth, "Creating window...\n");
    (*messageDepth)++;
    mWindow = SDL_CreateWindow("Program", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, mWindowWidth, mWindowHeight, SDL_WINDOW_SHOWN);
    if (mWindow == NULL)
    {
        Global::printDebug(logLevel, messageDepth, "Window could not be created: ");
        if ((*logLevel) > 0)
        {
            printf("%s\n", SDL_GetError());
        }
        return false;
    }
    (*messageDepth)--;
    Global::printInfo(logLevel, messageDepth, "Window created.\n");
    return true;
}
bool Window::createRenderer(const int *logLevel, int *messageDepth)
{
    Global::printInfo(logLevel, messageDepth, "Creating renderer for the window...\n");
    (*messageDepth)++;
    mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED);
    if (mRenderer == NULL)
    {
        Global::printDebug(logLevel, messageDepth, "Failed to create renderer: ");
        if ((*logLevel) > 0)
        {
            printf("%s\n", SDL_GetError());
        }
        return false;
    }
    SDL_SetRenderDrawColor(mRenderer, 255, 255, 255, 255);
    (*messageDepth)--;
    Global::printInfo(logLevel, messageDepth, "Renderer created. Drawcolour initialised to white.\n");

    return true;
}
bool Window::initialisePNGLoading(const int *logLevel, int *messageDepth)
{
    Global::printInfo(logLevel, messageDepth, "Initialising PNG loading...\n");
    (*messageDepth)++;
    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags))
    {
        Global::printDebug(logLevel, messageDepth, "Failed to initialise PNG loading: ");
        if ((*logLevel) > 0)
        {
            printf("%s\n", IMG_GetError());
        }
        return false;
    }
    (*messageDepth)--;
    Global::printInfo(logLevel, messageDepth, "PNG loading initialised.\n");

    return true;
}