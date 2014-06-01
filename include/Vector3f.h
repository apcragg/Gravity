#ifndef VECTOR3F_H
#define VECTOR3F_H

#include <math.h>
#include <sstream>
#include <string>
#include <iostream>

class Vector3f
{
    public:
        Vector3f() : x(0.0f), y(0.0f), z(0.0f) {}
        Vector3f(const Vector3f& cpy) : x(cpy.get_x()), y(cpy.get_y()), z(cpy.get_z()) {}
        Vector3f(float x, float y, float z) : x(x), y(y), z(z) {}
        inline void operator=(Vector3f& v) { x = v.get_x(); y = v.get_y(), z = v.get_z(); }
        inline void operator=(float f) { x = f; y = f; z = f; }

        inline float get_x() const { return x; }
        inline float get_y() const { return y; }
        inline float get_z() const { return z; }

        inline Vector3f add(const Vector3f& v) { return Vector3f(x + v.get_x(), y + v.get_y(), z + v.get_z()); }
        inline Vector3f sub(const Vector3f& v) { return Vector3f(x - v.get_x(), y - v.get_y(), z - v.get_z()); }
        inline Vector3f mul(float f) { return Vector3f(x * f, y * f, z * f); }
        inline Vector3f div(float f) { return Vector3f(x / f, y / f, z /f); }

        inline Vector3f operator+(const Vector3f& v) { return add(v); }
        inline Vector3f operator-(const Vector3f& v) { return sub(v); }
        inline Vector3f operator*(float f) { return mul(f); }
        inline Vector3f operator/(float f) { return div(f); }

        inline float dot(Vector3f& v) { return x * v.get_x() + y * v.get_y() + z * v.get_z(); }
        inline float length() { return (float) sqrt(x * x + y * y + z * z); }

        const std::string to_str()
        {
            std::ostringstream buff;
            buff << "x: " << x << ", y: " << y << ", z: " << z;
            return buff.str();
        }

        Vector3f cross(Vector3f&);

        virtual ~Vector3f();
    protected:
    private:
        float x, y,z;
};

#endif // VECTOR3F_H
