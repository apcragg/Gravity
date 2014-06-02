#ifndef RENDERINGENGINE_H
#define RENDERINGENGINE_H

#include "glew.h"
#include "glfw3.h"

#include <map>
#include <iostream>

#include "EngineObject.h"
#include "Shader.h"
#include "ValueMap.h"

class EngineObject;
class Shader;
class ValueMap;

class RenderingEngine
{
    public:
        RenderingEngine();

        void render_sceen(EngineObject*);
        void initialize();
        Shader* get_shader(std::string);

        inline ValueMap* get_value_map() { return m_value_map; }

        virtual ~RenderingEngine();
    protected:
    private:
        std::map<std::string, Shader*> m_shader_list;
        ValueMap* m_value_map;
};

#endif // RENDERINGENGINE_H
