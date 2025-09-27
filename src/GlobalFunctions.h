#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <memory>
#include <stdio.h> // Currently comes from sdl2 as well, but that's no guarantee.
#include <string>
#include <fstream>

void printCharNTimes(int *n, const char *c);
void printDebug(int *logLevel, int *messageDepth, const char *message);
void printInfo(int *logLevel, int *messageDepth, const char *message);