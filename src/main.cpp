#include "GameController.h"

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Check the makefile or run script!\n");
        return -1;
    }
    GameController gameController = GameController(argv[1]);
    gameController.startApplication();

    return 0;
}