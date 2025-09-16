#include "Window.h"

Window::Window()
{
    mWindow = NULL;
    mRenderer = NULL;
    mWindowWidth = 0;
    mWindowHeight = 0;
}
Window::Window(int width, int height)
{ // Currently not in use!
    mWindow = NULL;
    mRenderer = NULL;
    mWindowWidth = width;
    mWindowHeight = height;
}
Window::~Window()
{
}
bool Window::init(int *logLevel, int *messageDepth)
{
    getWindowDimensions(logLevel, messageDepth);

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
void Window::close(int *logLevel, int *messageDepth)
{
    printInfo(logLevel, messageDepth, "Destroying renderer...\n");
    SDL_DestroyRenderer(mRenderer);
    printInfo(logLevel, messageDepth, "Renderer destroyed.\n");
    printInfo(logLevel, messageDepth, "Destroying window...\n");
    SDL_DestroyWindow(mWindow);
    printInfo(logLevel, messageDepth, "Window destroyed.\n");
}

void Window::getWindowDimensions(int *logLevel, int *messageDepth)
{
    while (mWindowWidth < 10 || mWindowHeight < 10)
    {
        printf("\n***\n\n");
        while (mWindowWidth < 10)
        {
            printf("Enter preferred window width (min 10): ");
            scanf("%d", &mWindowWidth); // TODO - Non-numbers break the simple implementation
        }
        while (mWindowHeight < 10)
        {
            printf("Enter preferred window height (min 10): ");
            scanf("%d", &mWindowHeight); // TODO - Non-numbers break the simple implementation
        }
        printf("\n\n***\n\n");
    }
}
SDL_Renderer *Window::getRenderer() { return mRenderer; }
int Window::getWidth() { return mWindowWidth; }
int Window::getHeight() { return mWindowHeight; }

bool Window::createWindow(int *logLevel, int *messageDepth)
{
    printInfo(logLevel, messageDepth, "Creating window...\n");
    (*messageDepth)++;
    mWindow = SDL_CreateWindow("Program", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, mWindowWidth, mWindowHeight, SDL_WINDOW_SHOWN);
    if (mWindow == NULL)
    {
        printDebug(logLevel, messageDepth, "Window could not be created: ");
        if ((*logLevel) > 0)
        {
            printf("%s\n", SDL_GetError());
        }
        return false;
    }
    (*messageDepth)--;
    printInfo(logLevel, messageDepth, "Window created.\n");
    return true;
}
bool Window::createRenderer(int *logLevel, int *messageDepth)
{
    printInfo(logLevel, messageDepth, "Creating renderer for the window...\n");
    (*messageDepth)++;
    mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED);
    if (mRenderer == NULL)
    {
        printDebug(logLevel, messageDepth, "Failed to create renderer: ");
        if ((*logLevel) > 0)
        {
            printf("%s\n", SDL_GetError());
        }
        return false;
    }
    SDL_SetRenderDrawColor(mRenderer, 255, 255, 255, 255);
    (*messageDepth)--;
    printInfo(logLevel, messageDepth, "Renderer created. Drawcolour initialised to white.\n");

    return true;
}
bool Window::initialisePNGLoading(int *logLevel, int *messageDepth)
{
    printInfo(logLevel, messageDepth, "Initialising PNG loading...\n");
    (*messageDepth)++;
    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags))
    {
        printDebug(logLevel, messageDepth, "Failed to initialise PNG loading: ");
        if ((*logLevel) > 0)
        {
            printf("%s\n", IMG_GetError());
        }
        return false;
    }
    (*messageDepth)--;
    printInfo(logLevel, messageDepth, "PNG loading initialised.\n");

    return true;
}