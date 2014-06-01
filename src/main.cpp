#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

#include "glew.h"
#include "glfw3.h"

#include "MainEngine.h"
#include "Vector3f.h"
#include "Logger.h"

int main()
{
    Logger::get_instance()->set_verbose(false);

    MainEngine engine;

    return EXIT_SUCCESS;
}
