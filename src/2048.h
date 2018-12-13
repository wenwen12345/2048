/*
    2048
    ====
        Game 2048.
*/

#ifndef _2048_H_INCLUDED
#define _2048_H_INCLUDED

#include <array>

// Namespace Begin
namespace Game2048
{

using namespace std;

////////////////////////////////////////////////////////////////////////////////
// 2048 Game Class
////////////////////////////////////////////////////////////////////////////////

class Game
{
    private:

        // Game Map
        array<array<int, 4>, 4> __gameMap;

        // Step
        int __stepNum;

    public:

        // Init
        Game();

        // Show
        void show() const;

        // Create A New Number
        void createNewNum();

        // Press
        void pressLeft();
        void pressRight();
        void pressUp();
        void pressDown();

        // Check
        bool winCheck() const;
        bool loseCheck() const;

        // After Press
        void afterPress(const bool moveBool);

        // Run
        void Run();
};


// Namespace End
}


#endif