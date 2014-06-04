#ifndef VALUEMAP_H
#define VALUEMAP_H

#include "Math3D.h"
#include <map>

class ValueMap
{
public:
        ValueMap() {}

        inline void set_vector_3f(const std::string p_name, Vector3f p_vector_3f) { m_vector_3fs[p_name] = p_vector_3f; }
        inline Vector3f get_vector_3f(std::string p_name)
        {
            auto it = m_vector_3fs.find(p_name);
            if(it != m_vector_3fs.end())
                return it->second;

            return Vector3f(0.0f, 0.0f, 0.0f);
        }

        inline void set_float(std::string p_name, float p_float) { m_floats[p_name] = p_float; }
        inline float get_float(std::string p_name)
        {
            auto it = m_floats.find(p_name);
            if(it != m_floats.end())
                return it->second;

            return 0.0f;
        }

        inline void set_int(std::string p_name, int p_int) { m_floats[p_name] = p_int; }
        inline float get_int(std::string p_name)
        {
            auto it = m_ints.find(p_name);
            if(it != m_ints.end())
                return it->second;

            return 0;
        }

        virtual ~ValueMap() {}
    protected:
    private:
        std::map<std::string, Vector3f> m_vector_3fs;
        std::map<std::string, float> m_floats;
        std::map<std::string, int> m_ints;
};

#endif // VALUEMAP_H
