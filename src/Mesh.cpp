#include "Mesh.h"

std::map<std::string, Mesh::MeshData*> Mesh::s_mesh_lib;

Mesh::Mesh(const std::string& p_name) : m_mesh_name(p_name)
{
    if(s_mesh_lib.find(m_mesh_name) != s_mesh_lib.end());
    else
    {
        s_mesh_lib[m_mesh_name] = new MeshData;

        glGenBuffers(1, &(s_mesh_lib[m_mesh_name]->m_vbo));
        glGenBuffers(1, &(s_mesh_lib[m_mesh_name]->m_ibo));
        glGenBuffers(1, &(s_mesh_lib[m_mesh_name]->m_abo));

        load_mesh(m_mesh_name);
    }

}

void Mesh::draw()
{

}

void Mesh::load_mesh(const std::string& p_file_name)
{
    //loads the tet from file
    //initializes search varaibales
    std::string obj_text = Util::load_file(std::string("objs/").append(p_file_name), ".obj");
    std::string current_line = "";
    size_t start_of_line = 0;
    size_t end_of_line = 0;

    //searches through every line
    //identified by a newline character
    while((end_of_line = obj_text.find('\n', start_of_line)) != std::string::npos)
    {
        //identifies the line identifier token and
        //creates a string to hold the current line
        current_line = obj_text.substr(start_of_line, end_of_line - start_of_line);
        size_t ident_pos = Util::find_first_char(current_line);
        size_t end_ident = Util::find_first_whitespace(current_line, ident_pos);
        std::string ident = current_line.substr(ident_pos, end_ident);
        std::string current_values = current_line.substr(ident_pos + current_line.size() ? ident.size() : 0);

        std::vector<Vector3f> vertices_list;
        std::vector<Vector3f> normals_list;
        std::vector<Vector2f> uvs_list;

        //loads a vertex
        if(ident == "v")
        {
            float vertices[3];
            load_vec(current_values, 3, vertices);
            Vector3f v(vertices);
            vertices_list.push_back(v);
        }
        //loads a normal
        else if(ident == "vn")
        {
            float normals[3];
            load_vec(current_values, 3, normals);
            Vector3f n(normals);
            normals_list.push_back(n);
        }
        //loads uv coords
        else if(ident == "vt")
        {
            float uvs[2];
            load_vec(current_values, 2, uvs);
            Vector2f vt(uvs);
            uvs_list.push_back((vt));
        }
        //line is commented
        else if(ident == "#");

        start_of_line = end_of_line + 1;
    }

    //std::cout << "nigga we made it!\n";
}

void Mesh::load_vec(std::string& p_search_text, int p_size, float* p_vec)
{
    for(int i = 0; i < p_size; i++)
    {
        size_t start_float_loc = Util::find_first_char(p_search_text);
        size_t end_float_loc = Util::find_first_whitespace(p_search_text, start_float_loc);
        p_vec[i] = ::strtof(p_search_text.substr(start_float_loc, end_float_loc).c_str(), 0);
        p_search_text = p_search_text.substr(end_float_loc);
    }
}

Mesh::~Mesh()
{

}

void Mesh::free_resources()
{
    for(auto it = s_mesh_lib.begin(); it != s_mesh_lib.end(); it++)
    {
        delete it->second;
    }
}


