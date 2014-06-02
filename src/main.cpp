#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

#include "glew.h"
#include "glfw3.h"

#include "MainEngine.h"
#include "Vector3f.h"
#include "Logger.h"

#ifdef __CODEBLOCKS
#define PAUSE false
#else
#define PAUSE true
#endif // __CODEBLOCKS

int main()
{
    Logger::get_instance()->set_verbose(false);

    MainEngine engine;

    if(PAUSE)
    {
        std::cout << "Press Enter to continue. . .\n";
        std::cin.get();
    }

    return EXIT_SUCCESS;
}
