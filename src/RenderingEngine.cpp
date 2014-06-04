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

    for(int i = 0; i < 1; i++)
    {
        Mesh m("test");
    }

    //setting up shaders

    m_value_map = new ValueMap;

    m_shader_list.insert(std::pair<std::string, Shader*>(std::string("lolpenis"), new Shader("lolpenis")));
}

void RenderingEngine::render_sceen(EngineObject* p_engine_object)
{
    //pre rednder future stuff

    m_value_map->set_vector_3f(std::string("other_vec"), Vector3f(1.4f, 0.3f, -2.1f));
    m_value_map->set_float(std::string("other_vec"), 1.56f);

    get_shader("lolpenis")->update_uniforms(this);

    p_engine_object->render(this, m_shader_list["lolpenis"]);

    //post render future stuff
}

//does not exit gracefully
Shader* RenderingEngine::get_shader(std::string p_name)
{
    if(m_shader_list.find(p_name) != m_shader_list.end())
        return m_shader_list[p_name];
    else
    {
        std::cout << "FATAL ERROR: " << p_name << " is an unknow shader program!\nExiting. . .";
        exit(-1);
        return nullptr;
    }
}

RenderingEngine::~RenderingEngine()
{
    //clears the list of shaders
    //auto is fucking awesome and useful
    for(auto it = m_shader_list.begin(); it != m_shader_list.end(); it++)
    {
        //deletes the second value of the pair currently pointed to by the iterator
        delete it->second;
    }

    delete m_value_map;
}
