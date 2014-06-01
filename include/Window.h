#ifndef WINDOW_H
#define WINDOW_H

#include "glew.h"
#include "glfw3.h"

#include "Logger.h"

class Window
{
    public:
        Window(int, int);

        void open_window();
        void destroy_window();
        void render();
        void clear_screen();
        void clear_screen(float, float, float);

        bool is_closed_requested();

        int get_width();
        int get_height();

        GLFWwindow* get_window();

        virtual ~Window();
    protected:
    private:
        int mWidth, mHeight;
        GLFWwindow* mWindow;
};

void key_callback(GLFWwindow*, int, int, int, int);

#endif // WINDOW_H
