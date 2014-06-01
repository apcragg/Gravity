#ifndef RENDERINGENGINE_H
#define RENDERINGENGINE_H

#include "glew.h"
#include "glfw3.h"

#include <map>

#include "EngineObject.h"
#include "Shader.h"

class EngineObject;
class Shader;

class RenderingEngine
{
    public:
        RenderingEngine();

        void render_sceen(EngineObject*);
        void initialize();

        virtual ~RenderingEngine();
    protected:
    private:
        std::map<std::string, Shader*> m_shader_list;
};

#endif // RENDERINGENGINE_H
