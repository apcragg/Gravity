#ifndef MESH_H
#define MESH_H

#include "glew.h"
#include "glfw3.h"

#include <string>
#include <cstdlib>
#include <map>
#include <vector>

#include "Util.h"
#include "Vector3f.h"
#include "Vector2f.h"

class Vector3f;

class Mesh
{
    public:
        Mesh(const std::string&);

        void draw();
        inline std::string get_name() { return m_mesh_name; }

        static void free_resources();

        virtual ~Mesh();
    protected:
    private:
         struct MeshData
        {
            GLuint m_vbo;
            GLuint m_ibo;
            GLuint m_abo;
            int m_size;
        };

        static std::map<std::string, MeshData*> s_mesh_lib;

        void load_mesh(const std::string&);
        void load_vec(std::string&, int, float*);
        static std::string load_file(const std::string&);

        std::string m_mesh_name;
};

#endif // MESH_H
