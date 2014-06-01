#include "EngineObject.h"

EngineObject::EngineObject() : m_main_engine(nullptr)
{

}

void EngineObject::update()
{
    //nothing for now
}

void EngineObject::render(RenderingEngine* p_rendering_engine, Shader* shader)
{
    //nothing for now
}

void EngineObject::add_object(EngineObject* p_object)
{
    p_object->set_engine(m_main_engine);
    p_object->set_parent(this);
    m_children.push_back(p_object);
}

void EngineObject::add_component(EngineComponent* p_component)
{
    p_component->set_parent(this);
    m_components.push_back(p_component);
}

void EngineObject::set_parent(EngineObject* p_parent)
{
    m_parent_object = p_parent;
}

void EngineObject::set_engine(MainEngine* p_main_engine)
{
    m_main_engine = p_main_engine;
}

EngineObject::~EngineObject()
{
    //dtor
}
