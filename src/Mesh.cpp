#include "Mesh.h"

Mesh::Mesh(std::string p_name) : m_mesh_name(p_name)
{
    glGenBuffers(1, &m_mesh_data.m_vbo);
    glGenBuffers(1, &m_mesh_data.m_ibo);
    glGenBuffers(1, &m_mesh_data.m_abo);

    load_mesh(m_mesh_name);
}

void Mesh::draw()
{

}

void Mesh::load_mesh(std::string p_file_name)
{
    std::string obj_text = load_file(p_file_name);
    size_t start_of_line = 0;
    size_t end_of_line;

    while((end_of_line = obj_text.find('\n', start_of_line)) != std::string::npos)
    {
       // std::cout << obj_text.substr(start_of_line, end_of_line - start_of_line) << '\n';
        start_of_line = end_of_line + 1;
    }

    std::cout << "nigga we made it!\n";
}

Mesh::~Mesh()
{
    //dtor
}

std::string Mesh::load_file(std::string p_file_name)
{
    std::string shader_text;
    std::ifstream in_file;

	std::string path = std::string("./res/objs/");
	path.append(p_file_name).append(".obj");

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

