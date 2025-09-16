#include "Window.h"

Window::Window()
{
    mWindow = NULL;
    mScreenSurface = NULL;
}
Window::~Window()
{
}
bool Window::init(int *logLevel, int *messageDepth)
{
    printInfo(logLevel, messageDepth, "Creating window...\n");
    (*messageDepth)++;

    mWindow = SDL_CreateWindow("Program", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);
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

    printInfo(logLevel, messageDepth, "Setting window surface to grey to finish off initialisation...\n");
    mScreenSurface = SDL_GetWindowSurface(mWindow);
    SDL_FillRect(mScreenSurface, NULL, SDL_MapRGB(mScreenSurface->format, 60, 60, 60));
    SDL_UpdateWindowSurface(mWindow);
    printInfo(logLevel, messageDepth, "Success. Window is ready.\n");

    return true;
}
void Window::close()
{
    SDL_DestroyWindow(mWindow);
}