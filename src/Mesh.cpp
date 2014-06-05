#include "Mesh.h"

std::map<std::string, Mesh::MeshData*> Mesh::s_mesh_lib;

Mesh::Mesh(const std::string& p_name) : m_mesh_name(p_name)
{
    if(s_mesh_lib.find(m_mesh_name) != s_mesh_lib.end()) m_mesh_data = s_mesh_lib[m_mesh_name];
    else
    {
        s_mesh_lib[m_mesh_name] = new MeshData;

        glGenBuffers(3, (s_mesh_lib[m_mesh_name]->m_buffer_objects));
        glGenVertexArrays(1, &(s_mesh_lib[m_mesh_name]->m_vertex_array_object));

        m_mesh_data = s_mesh_lib[m_mesh_name];

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

    //temp vectors to hold all read in data
    std::vector<Vector3f> vertices_list;
    std::vector<Vector3f> normals_list;
    std::vector<Vector2f> uvs_list;
    std::vector<Vector3i> index_list;

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
        //face indicies
        else if(ident == "f")
        {
            std::string index_line = current_values;

            for(int i = 0; i < 3; i++)
            {
                Vector3i vertex_index;

                size_t start_index = Util::find_first_char(index_line);
                size_t end_index = Util::find_first_whitespace(index_line, start_index);

                int j = 0;
                char current_char;
                size_t k = start_index;
                std::string index = "";

                while((current_char = index_line[k]) != ' ' && current_char != '\n' && k <= end_index)
                {
                    if(current_char == '/' && index_line[k+1] != '/')
                    {
                        vertex_index[j] = ::strtol(index.c_str(), nullptr, 0);
                        index = "";
                        j++;
                    }
                    else if(index_line[k + 1] == ' ' || index_line[k + 1] == '\n')
                    {
                        index += current_char;
                        vertex_index[j] =::strtol(index.c_str(), nullptr, 0);
                    }
                    else
                        index += current_char;

                   k++;
                }

                index_line = index_line.substr(end_index);
                index_list.push_back(vertex_index);
            }
        }
        //line is commented
        else if(ident == "#");

        start_of_line = end_of_line + 1;
    }

    Vector3f v[index_list.size()];
    Vector3f n[index_list.size()];
    Vector2f u[index_list.size()];
    int indices[index_list.size()];

    for(size_t i =0; i < index_list.size(); i++)
    {
        v[i] = vertices_list[index_list[i].get_x()];
        u[i] = uvs_list[index_list[i].get_x()];
        n[i] = normals_list[index_list[i].get_z()];
        indices[i] = i;
    }

    upload_mesh_data(indices, v, n, u, index_list.size());

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

void Mesh::upload_mesh_data(int* p_indices, Vector3f* p_vertices, Vector3f* p_normals, Vector2f* p_uvs, int size)
{
  glBindVertexArray(m_mesh_data->m_vertex_array_object);

  glBindBuffer(GL_ARRAY_BUFFER, m_mesh_data->m_buffer_objects[VERT_BO]);

  glBindBuffer(GL_ARRAY_BUFFER, m_mesh_data->m_buffer_objects[NORM_BO]);

  glBindBuffer(GL_ARRAY_BUFFER, m_mesh_data->m_buffer_objects[UV_BO]);

  glBindBuffer(GL_ARRAY_BUFFER, 0);

  glBindVertexArray(0);
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


