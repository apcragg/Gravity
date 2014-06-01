#ifndef MAINENGINE_H
#define MAINENGINE_H

#include "Logger.h"
#include "RenderingEngine.h"
#include "EngineObject.h"

#include "glew.h"
#include "glfw3.h"

class RenderingEngine;
class EngineObject;

class MainEngine
{
    public:
        MainEngine();

        inline EngineObject* get_root_object() { return m_root_object; }
        inline RenderingEngine* get_rendering_engine() { return m_rendering_engine; }
        inline void set_rendering_engine(RenderingEngine* p_rendering_engine) { m_rendering_engine = p_rendering_engine; }

        virtual ~MainEngine();
    protected:
    private:
        RenderingEngine* m_rendering_engine;
        EngineObject* m_root_object;

};

#endif // MAINENGINE_H
