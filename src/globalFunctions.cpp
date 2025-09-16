#include "globalFunctions.h"

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