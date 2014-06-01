#ifndef SHADER_H
#define SHADER_H

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <regex>
#include <math.h>

#include "glew.h"
#include "glfw3.h"

#include "Logger.h"

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

        bool uniform_exists(const std::string);

        virtual ~Shader();
    protected:
    private:
        GLuint m_program;
        std::string m_name;
        std::vector<std::pair<std::string, GLint>> m_uniform_locations;
        std::vector<std::pair<std::string, std::string>> m_uniform_type;


};

#endif // SHADER_H
