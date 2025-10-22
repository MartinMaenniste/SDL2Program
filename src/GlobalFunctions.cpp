#include "GlobalFunctions.h"

void Global::printCharNTimes(const int *n, const char *c)
{
    for (int i = 0; i < (*n); i++)
    {
        printf(c);
    }
}
void Global::printDebug(const int *logLevel, const int *messageDepth, const char *message)
{
    if ((*logLevel) > 0)
    {
        Global::printCharNTimes(messageDepth, "==");
        printf("> ");
        printf(message);
    }
}
void Global::printInfo(const int *logLevel, const int *messageDepth, const char *message)
{

    if ((*logLevel) > 1)
    {
        Global::printCharNTimes(messageDepth, "==");
        printf("> ");
        printf(message);
    }
}
bool Global::areColliding(const SDL_Rect &first, const SDL_Rect &second)
{
    return Global::areCollidingX(first, second) && Global::areCollidingY(first, second);
}
bool Global::areCollidingX(const SDL_Rect &first, const SDL_Rect &second)
{
    // first.left has to be smaller than second.right  - first is somewhere to the left of second
    // &&
    // first.right has to be bigger than second.left   - first is somewhere to the right of second
    //                                                  if first is only left or only right, then not colliding. Has to be both

    return (first.x < second.x + second.w && first.x + first.w > second.x);
}
bool Global::areCollidingY(const SDL_Rect &first, const SDL_Rect &second)
{
    return (first.y < second.y + second.h && first.y + first.h > second.y);
}
bool Global::isInRect(const int x, const int y, const SDL_Rect &rect)
{
    return (x >= rect.x && x < rect.x + rect.w && y >= rect.y && y < rect.y + rect.h);
}