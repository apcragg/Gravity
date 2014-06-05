#include "Window.h"
#include <iostream>
#include <stdlib.h>

Window::Window(int pWidth, int pHeight) : mWidth(pWidth), mHeight(pHeight)
{

}

void Window::open_window()
{
    mWindow = glfwCreateWindow(mWidth, mHeight, "Generic Window", NULL, NULL);

    if(!mWindow)
    {
        std::cout << "Failed to create window...";
        glfwTerminate();
        exit(-1);
    }

    if(glfwGetCurrentContext() != mWindow)
        glfwMakeContextCurrent(mWindow);

    glfwSetKeyCallback(mWindow, key_callback);

    LOG("Created window");
}

void Window::destroy_window()
{
    glfwDestroyWindow(mWindow);
}

void Window::render()
{
    glfwSwapBuffers(mWindow);
}

void Window::clear_screen()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::clear_screen(float r, float g, float b)
{
    glClearColor(r, g, b, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

bool Window::is_closed_requested()
{
    return glfwWindowShouldClose(mWindow);
}

int Window::get_height()
{
    return mHeight;
}

int Window::get_width()
{
    return mWidth;
}

GLFWwindow* Window::get_window()
{
    return mWindow;
}

void key_callback(GLFWwindow* pWindow, int pKey, int pScanCode, int pAction, int pMods)
{

}

Window::~Window()
{
    glfwDestroyWindow(mWindow);
}
