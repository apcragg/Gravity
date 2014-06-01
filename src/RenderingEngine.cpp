#include "RenderingEngine.h"

RenderingEngine::RenderingEngine()
{
    initialize();
}

void RenderingEngine::initialize()
{
    //setting up OpenGL states

    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);

    glClearColor(0.65f, 0.5f, 0.9f, 1.0f);

    //setting up shaders

    m_shader_list.insert(std::pair<std::string, Shader*>(std::string("lolpenis"), new Shader("lolpenis")));
}

void RenderingEngine::render_sceen(EngineObject* p_engine_object)
{
    //pre rednder future stuff

    p_engine_object->render(this, m_shader_list["lolpenis"]);

    //post render future stuff
}

RenderingEngine::~RenderingEngine()
{
    //clears the list of shaders
    //auto is fucking awesome and useful
    for(auto it = m_shader_list.begin(); it != m_shader_list.end(); it++)
    {
        //deletes the second value of the pair currently pointed to by the iterator
        delete (*it).second;
    }
}
