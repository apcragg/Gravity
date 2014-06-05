#ifndef MESH_H
#define MESH_H

#include "glew.h"
#include "glfw3.h"

#include <string>
#include <cstdlib>
#include <map>
#include <vector>

#include "Util.h"
#include "Math3D.h"

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
            GLuint m_buffer_objects[3];
            GLuint m_vertex_array_object;
            int m_size;

            std::vector<Vector3f> m_vertices;
            std::vector<Vector2f> m_uvs;
            std::vector<Vector3f> m_normals;
        };

        enum
        {
            VERT_BO,
            NORM_BO,
            UV_BO
        };

        static std::map<std::string, MeshData*> s_mesh_lib;
        static std::string load_file(const std::string&);

        void load_mesh(const std::string&);
        void load_vec(std::string&, int, float*);
        void upload_mesh_data(int*, Vector3f*, Vector3f*, Vector2f*, int);

        std::string m_mesh_name;
        MeshData* m_mesh_data;
};

#endif // MESH_H
