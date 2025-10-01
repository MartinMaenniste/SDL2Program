#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <memory>
#include <stdio.h> // Currently comes from sdl2 as well, but that's no guarantee.
#include <string>
#include <fstream>
#include <vector>

void printCharNTimes(int *n, const char *c);
void printDebug(int *logLevel, int *messageDepth, const char *message);
void printInfo(int *logLevel, int *messageDepth, const char *message);
bool areColliding(SDL_Rect &first, SDL_Rect &second);
bool areCollidingX(SDL_Rect &first, SDL_Rect &second);
bool areCollidingY(SDL_Rect &first, SDL_Rect &second);