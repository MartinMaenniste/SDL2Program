#include "GlobalFunctions.h"

void printCharNTimes(int *n, const char *c)
{
    for (int i = 0; i < (*n); i++)
    {
        printf(c);
    }
}
void printDebug(int *logLevel, int *messageDepth, const char *message)
{
    if ((*logLevel) > 0)
    {
        printCharNTimes(messageDepth, "==");
        printf("> ");
        printf(message);
    }
}
void printInfo(int *logLevel, int *messageDepth, const char *message)
{

    if ((*logLevel) > 1)
    {
        printCharNTimes(messageDepth, "==");
        printf("> ");
        printf(message);
    }
}
bool areColliding(SDL_Rect &first, SDL_Rect &second)
{
    return areCollidingX(first, second) && areCollidingY(first, second);
}
bool areCollidingX(SDL_Rect &first, SDL_Rect &second)
{
    // first.left has to be smaller than second.right  - first is somewhere to the left of second
    // &&
    // first.right has to be bigger than second.left   - first is somewhere to the right of second
    //                                                  if first is only left or only right, then not colliding. Has to be both

    return (first.x < second.x + second.w && first.x + first.w > second.x);
}
bool areCollidingY(SDL_Rect &first, SDL_Rect &second)
{
    return (first.y < second.y + second.h && first.y + first.h > second.y);
}
