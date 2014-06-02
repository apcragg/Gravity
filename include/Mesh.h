#ifndef MESH_H
#define MESH_H

#include "glew.h"
#include "glfw3.h"

#include <string>
#include <fstream>
#include <iostream>


class Mesh
{
    public:
        Mesh(const std::string);

        void draw();
        inline std::string get_name() { return m_mesh_name; }

        virtual ~Mesh();
    protected:
    private:
        void load_mesh(std::string);
        static std::string load_file(std::string);

        struct MeshData
        {
            GLuint m_vbo;
            GLuint m_ibo;
            GLuint m_abo;
            int m_size;
        };

    MeshData m_mesh_data;
    std::string m_mesh_name;
};

#endif // MESH_H
