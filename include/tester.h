#ifndef TESTER_H
#define TESTER_H
#include "glew.h"
#include "glfw3.h"

#include <iostream>

class tester
{
    public:
        tester();
        virtual ~tester();

        void shout();
        static void input(GLFWwindow*, int, int, int, int);
    protected:
    private:
};

#endif // TESTER_H
