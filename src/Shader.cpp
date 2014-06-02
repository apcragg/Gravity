#include "Shader.h"

static std::string load_shader(const std::string p_file_name);

Shader::Shader(std::string p_name) : m_name(p_name)
{
    initialize();
}

void Shader::initialize()
{
   m_program = glCreateProgram();

   if(!m_program)
        LOGGER << std::string("Failed to create shader program ").append(m_name);
   else
        LOGGER << std::string("Succesfuly initialized shader program ").append(m_name);

    std::string vertex_shader = load_shader(std::string(m_name).append(".vs"));
    std::string fragment_shader = load_shader(std::string(m_name).append(".fs"));

    add_shader(vertex_shader, GL_VERTEX_SHADER);
    add_shader(fragment_shader, GL_FRAGMENT_SHADER);

    link_shader();

    add_all_uniforms(vertex_shader);
    add_all_uniforms(fragment_shader);

    bind();
}

//================================================================//
//                 Program Constuction Methods
//================================================================//

void Shader::bind()
{
    glUseProgram(m_program);
}

void Shader::link_shader()
{
        glLinkProgram(m_program);

		GLint link_status;
		glGetProgramiv(m_program, GL_LINK_STATUS, &link_status);

		if (link_status == GL_FALSE)
		{
			LOGGER << std::string("Failed to link shader progam ").append(m_name);

			GLchar log[2048]; //allocates 2kB for the log.
			glGetProgramInfoLog(m_program, 2048, nullptr, log);

			LOGGER << log;
		}

		glValidateProgram(m_program);

		GLint validation_status;
        glGetProgramiv(m_program, GL_VALIDATE_STATUS, &validation_status);

		if (validation_status == GL_FALSE)
		{
			LOGGER << std::string("Failed to validate progam: ").append(m_name);

			GLchar log[2048]; //allocates 2kB for the log.
			glGetProgramInfoLog(m_program, 2048, nullptr, log);

			LOGGER << log;
		}
}

void Shader::add_shader(const std::string& p_shader_text, GLuint p_shader_type)
{
    GLuint shader = glCreateShader(p_shader_type);

    if(shader < 0)
        LOGGER << std::string("Failed to create shader program in ").append(m_name);
    else
    {
        //this is so needless for what I'm doing
        //very rarely is c++ more verbose than java
        const GLchar* text[1];
        text[0] = p_shader_text.c_str();
        GLint length[1];
        length[0] = p_shader_text.length();
;
        glShaderSource(shader, 1, text, length);
        glCompileShader(shader);
        glAttachShader(m_program, shader);
    }
}

//================================================================//
//                        Uniform Methods
//================================================================//

void Shader::add_uniform(std::string p_uniform_name, std::string p_unifom_type)
{
    GLint location = glGetUniformLocation(m_program, p_uniform_name.c_str());

    if(location < 0)
        LOGGER << std::string("Failed to create uniform ").append(p_uniform_name);
    else
    {
        m_uniform_locations[p_uniform_name] = location;
        m_uniform_types[p_uniform_name] = p_unifom_type;
    }
}

void Shader::add_all_uniforms(const std::string& p_shader_text)
{
    const static std::string uniform_token = "uniform";

    //location of the first token
    size_t token_location = p_shader_text.find(uniform_token);

    //a copy of the shader tex
    //used to preserve the original string reference
    std::string current_search = p_shader_text;

    //while there are still tokens being found
    while(token_location != std::string::npos)
    {
        std::cout << "loc: " << token_location << '\n';

        size_t last_line = current_search.rfind(';', token_location);
        bool is_commented = false;

        //if it isn't the first line of the file
        if(last_line != std::string::npos)
        {
            std::string search_string = current_search.substr(last_line, token_location);
            size_t comment_location = search_string.find("//");

            is_commented = comment_location != std::string::npos;
        }

        if(!is_commented)
        {
            size_t end = current_search.find(';', token_location);
            size_t type_start = token_location + uniform_token.size() + 1; //default

            for(size_t it = token_location + uniform_token.size(); it < end; it++)
            {
                if(current_search[it] == ' ' || current_search[it] == '\n') continue;

                type_start = it;
                it = end;
            }

            //debug code
            std::string uniform_type = current_search.substr(type_start, current_search.find(' ', type_start) - type_start);
            std::cout << "TYPE: " << uniform_type << ':' << '\n';

            size_t uniform_name_start = type_start + uniform_type.size(); //default

            for(size_t it = uniform_name_start; it < end; it++)
            {
                if(current_search[it] == ' ' || current_search[it] == '\n') continue;

                uniform_name_start = it;
                it = end;
            }

            size_t uniform_name_end = std::fmin(current_search.find(' ', uniform_name_start), current_search.find(';', uniform_name_start)) - uniform_name_start;

            //debug code
            std::string uniform_name = current_search.substr(uniform_name_start, uniform_name_end);
            std::cout << "NAME: " << uniform_name << ':' << '\n';

            add_uniform(uniform_name, uniform_type);
        }

        //starts the next search at the end of the current token
        current_search = current_search.substr(token_location + uniform_token.size(), current_search.size());

        //searches for the next token for the next iteration of the loop
        token_location = current_search.find(uniform_token);
    }

}

void Shader::update_uniforms(RenderingEngine* p_rendering_engine)
{
    for(auto it = m_uniform_types.begin(); it != m_uniform_types.end(); ++it)
    {
        std::string name = it->first;
        std::string type = it->second;

        if(type == "vec3")
            set_uniform_3f(name, p_rendering_engine->get_value_map()->get_vector_3f(name));
        else if(type == "float")
            set_uniform_f(name, p_rendering_engine->get_value_map()->get_float(name));
        else if(type == "int")
            set_uniform_i(name, p_rendering_engine->get_value_map()->get_int(name));
    }
}

void Shader::set_uniform_3f(std::string& p_name, const Vector3f& p_vector)
{
    glUniform3f(m_uniform_locations[p_name], p_vector.get_x(), p_vector.get_y(), p_vector.get_z());
}

void Shader::set_uniform_f(std::string& p_name, const float& p_float)
{
    glUniform1f(m_uniform_locations[p_name], p_float);
}

void Shader::set_uniform_i(std::string& p_name, const int& p_int)
{
    glUniform1i(m_uniform_locations[p_name], p_int);
}

bool Shader::uniform_exists(const std::string p_uniform_name)
{
    bool found = false;

    for(auto it = m_uniform_locations.begin(); it != m_uniform_locations.end(); ++it)
    {
        if(p_uniform_name.compare((*it).first) == 0)
            found = true;
    }

    return found;
}

Shader::~Shader()
{
    //dtor
}

//================================================================//
//                     Static loading methods
//================================================================//

static std::string load_shader(const std::string p_file_name)
{
    std::string shader_text;
    std::ifstream in_file;

	std::string path = std::string("./res/shaders/");
	path.append(p_file_name);

    in_file.open(path.c_str());

    if(in_file.is_open())
    {
        while(in_file.good())
        {
            std::string line;
            std::getline(in_file, line);
            shader_text.append(line + "\n");
        }
    }

    in_file.close();

    return shader_text;
}
