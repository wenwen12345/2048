/*
    Main program define.
*/

#include "2048.h"

int main()
{
    auto gameObj = Game2048::Game();
    gameObj.Run();

    return 0;
}