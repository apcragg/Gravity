#include "MainEngine.h"
#include "Logger.h"
#include "Window.h"

MainEngine::MainEngine()
{
    glfwInit();

    Window* window = new Window(720, 480);
    window->open_window();

    GLuint result = glewInit();

    if(result != GLEW_OK)
        exit(-1);

    LOGGER << "GL Contex Version: " + std::string((char*) glGetString(GL_VERSION));

    set_rendering_engine(new RenderingEngine());
    m_root_object = new EngineObject();

    while(!window->is_closed_requested())
    {
        window->clear_screen(0.4f, 0.2f, 0.8f);

        m_rendering_engine->render_sceen(m_root_object);

        window->render();
        glfwPollEvents();
    }

    Logger::get_instance()->dump();

    delete window;
}

MainEngine::~MainEngine()
{
    delete m_rendering_engine;
    delete m_root_object;
}
