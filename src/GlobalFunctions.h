#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <memory>
#include <stdio.h> // Currently comes from sdl2 as well, but that's no guarantee.
#include <string>
#include <fstream>
#include <vector>

namespace Global
{
    // Global functions
    void printCharNTimes(const int *n, const char *c);
    void printDebug(const int *logLevel, const int *messageDepth, const char *message);
    void printInfo(const int *logLevel, const int *messageDepth, const char *message);
    bool areColliding(const SDL_Rect &first, const SDL_Rect &second);
    bool areCollidingX(const SDL_Rect &first, const SDL_Rect &second);
    bool areCollidingY(const SDL_Rect &first, const SDL_Rect &second);
    bool isInRect(const int x, const int y, const SDL_Rect &rect);

    // Enum to create alias for item codes
    enum Items
    {
        TEST,
    };

    // Global variables
    // const SDL_Rect ITEM = {0, 0, 16, 16};
}