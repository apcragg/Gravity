#ifndef MATH3D_H
#define MATH3D_H

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
        Vector3f(float* f) : x(f[0]), y(f[1]), z(f[2]) {}
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

        inline void normalize() { x /= length(); y /= float(); z /= length(); }
        inline Vector3f normalized() { Vector3f v(*this); v.normalize(); return v; }

        const std::string to_str()
        {
            std::ostringstream buff;
            buff << "x: " << x << ", y: " << y << ", z: " << z;
            return buff.str();
        }

        Vector3f cross(Vector3f&) { return Vector3f(); }

        virtual ~Vector3f() {}
    protected:
    private:
        float x, y,z;
};

class Vector2f
{
    public:
        Vector2f() : x(0.0f), y(0.0f) {}
        Vector2f(float p_x, float p_y) : x(p_x), y(p_y) {}
        Vector2f(float* p_f) : x(p_f[0]), y(p_f[1]) {}
        Vector2f(const Vector2f& p_v) : x(p_v.get_x()), y(p_v.get_y()) {}

        inline float get_x() const { return x; }
        inline float get_y() const{ return y; }
        inline void set_x(float p_x) { x = p_x; }
        inline void set_y(float p_y) { y = p_y; }

        inline float length() { return sqrt(x * x + y * y); }
        inline Vector2f normalized() { Vector2f v(*this); v.normalize(); return v; }
        inline void normalize() { x /= length(); y /= length(); }

        const std::string to_str()
        {
            std::ostringstream buff;
            buff << "x: " << x << ", y: " << y;
            return buff.str();
        }

        virtual ~Vector2f() {}
    protected:
    private:
        float x, y;
};

class Matrix4f
{
    public:
        Matrix4f() { init(); }
        Matrix4f(const Matrix4f& p_cpy) { for(int i = 0; i < 16; i++) m_matrix[i % 4][ i / 4] = p_cpy.at(i % 4, i / 4); }

        inline float at(int i, int j) const { return m_matrix[i][j]; }
        inline void init()
        {
            for(int i = 0; i < 4; i++)
                for(int j = 0; j < 4; j++)
                    m_matrix[i][j] = i == j ? 1 : 0;
        }

    protected:

    private:
        float m_matrix[4][4];
};

#endif // MATH3D_H
