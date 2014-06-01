#ifndef ENGINEOBJECT_H
#define ENGINEOBJECT_H

#include <vector>
#include "EngineComponent.h"
#include "MainEngine.h"
#include "RenderingEngine.h"
#include "Shader.h"

class RenderingEngine;
class MainEngine;

class EngineObject
{
    public:
        EngineObject();

        void add_object(EngineObject*);
        void add_component(EngineComponent*);
        void set_parent(EngineObject*);
        void set_engine(MainEngine*);

        virtual void update();
        virtual void render(RenderingEngine*, Shader*);

        virtual ~EngineObject();
    protected:
    private:
        std::vector<EngineObject*> m_children;
        std::vector<EngineComponent*> m_components;
        EngineObject* m_parent_object;
        MainEngine* m_main_engine;
};

#endif // ENGINEOBJECT_H
