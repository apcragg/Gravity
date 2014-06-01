#ifndef GAME_H
#define GAME_H

#include "tester.h"

class Game
{
    public:
        Game();

        void input();
        void input(GLFWwindow*, int, int, int, int);

        float getxOffset();
        float getyOffset();

        virtual ~Game();
    protected:
    private:
           float xOff, yOff;

};

#endif // GAME_H
