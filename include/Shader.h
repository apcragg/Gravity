#ifndef SHADER_H
#define SHADER_H

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <map>
#include <regex>
#include <math.h>

#include "glew.h"
#include "glfw3.h"

#include "Logger.h"
#include "RenderingEngine.h"
#include "Math3D.h"
#include "Util.h"

class RenderingEngine;

class Shader
{
    public:
        Shader(std::string);

        void initialize();
        void bind();
        void add_shader(const std::string&, GLuint);
        void link_shader();
        void add_uniform(std::string, std::string);
        void add_all_uniforms(const std::string&);
        void update_uniforms(RenderingEngine*);

        void set_uniform_3f(std::string&, const Vector3f&);
        void set_uniform_f(std::string&, const float&);
        void set_uniform_i(std::string&, const int&);

        bool uniform_exists(const std::string);

        virtual ~Shader();
    protected:
    private:
        GLuint m_program;
        std::string m_name;
        std::map<std::string, GLint> m_uniform_locations;
        std::map<std::string, std::string> m_uniform_types;


};

#endif // SHADER_H
