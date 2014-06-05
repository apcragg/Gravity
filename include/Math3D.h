#ifndef MATH3D_H
#define MATH3D_H

#include <math.h>
#include <sstream>
#include <string>
#include <iostream>

#include "Util.h"

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
        float x, y, z;
};

class Vector3i
{
    public:
        Vector3i() : x(0), y(0) {}
        Vector3i(int p_x, int p_y, int p_z) : x(p_x), y (p_y), z(p_z) {}
        Vector3i(const Vector3i& p_cpy) : x(p_cpy.get_x()), y(p_cpy.get_y()), z(p_cpy.get_z()) {}

        inline int get_x() const { return x; }
        inline int get_y() const { return y; }
        inline int get_z() const { return z; }

        inline void set_x(int p_x) { x = p_x; }
        inline void set_y(int p_y) { y = p_y; }
        inline void set_z(int p_z) { z = p_z; }

        inline int& operator[](const int i) { return i == 0 ? x : (i == 1 ? y : z); }

        const std::string to_str()
        {
            std::ostringstream buff;
            buff << "x: " << x << ", y: " << y << " z: " << z;
            return buff.str();
        }

        virtual ~Vector3i() {}
    protected:
    private:
        int x, y, z;
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

        inline Vector2f add(const Vector2f& v) { return Vector2f(x + v.get_x(), y + v.get_y()); }
        inline Vector2f sub(const Vector2f& v) { return Vector2f(x - v.get_x(), y - v.get_y()); }
        inline Vector2f mul(float f) { return Vector2f(x * f, y * f); }
        inline Vector2f div(float f) { return Vector2f(x / f, y / f); }

        inline Vector2f operator+(const Vector2f& v) { return add(v); }
        inline Vector2f operator-(const Vector2f& v) { return sub(v); }
        inline Vector2f operator*(float f) { return mul(f); }
        inline Vector2f operator/(float f) { return div(f); }

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
        Matrix4f(const Matrix4f& p_cpy) { for(int i = 0; i < 16; i++) m_matrix[i / 4][ i % 4] = p_cpy.at(i / 4, i % 4); }

        inline float at(int i, int j) const { return m_matrix[i][j]; }
        inline Matrix4f init()
        {
            for(int i = 0; i < 4; i++)
                for(int j = 0; j < 4; j++)
                    m_matrix[i][j] = i == j ? 1.0f : 0.0f;

            return *this;
        }

        inline Matrix4f set_translation(const Vector3f& p_trans)
        {
            m_matrix[0][3] = p_trans.get_x();
            m_matrix[1][3] = p_trans.get_y();
            m_matrix[2][3] = p_trans.get_z();

            return *this;
        }

        inline Matrix4f set_scale(float p_scale)
        {
            m_matrix[0][0] = p_scale;
            m_matrix[1][1] = p_scale;
            m_matrix[2][2] = p_scale;

            return *this;
        }

        inline Matrix4f mul(const Matrix4f& p_other) const
        {
            Matrix4f p;
            for(int i = 0; i < 4; i++)
                for(int j = 0; j < 4; j++)
                {
                    p.m_matrix[i][j] = 0;
                    for(int k = 0; k < 4; k++)
                        p.m_matrix[i][j] += m_matrix[i][k] * p_other.m_matrix[k][j];
                }

            return p;
        }

        inline Matrix4f init_perspective(float p_fov, float p_aspect_ratio, float p_z_near, float p_z_far)
        {
            const float z_range = p_z_near - p_z_far;
            const float tan_hfov = tanf(p_fov / 2.0f);

            m_matrix[0][0] = 1.0f /(tan_hfov * p_aspect_ratio); m_matrix[0][1] = 0.0f;          m_matrix[0][2] = 0.0f;                              m_matrix[0][3] = 0.0f;
            m_matrix[1][0] = 0.0f;                              m_matrix[1][1] = 1.0f/tan_hfov; m_matrix[1][2] = 0.0f;                              m_matrix[1][3] = 0.0f;
            m_matrix[2][0] = 0.0f;                              m_matrix[2][1] = 0.0f;          m_matrix[2][2] = (-p_z_near - p_z_far)/z_range;     m_matrix[2][3] = 1.0f;
            m_matrix[3][0] = 0.0f;                              m_matrix[3][1] = 0.0f;          m_matrix[3][2] = 2.0f * p_z_far * p_z_near/z_range; m_matrix[3][3] = 0.0f;

            return *this;
        }

        inline Matrix4f operator*(const Matrix4f& p_other) { return mul(p_other); }
        inline Matrix4f operator*(const float p_mul) { return set_scale(p_mul); }

        inline std::string to_str()
        {
            std::string s;
            for(int i = 0; i < 16; i++)
                s.append("[" + Util::num_to_str(m_matrix[i / 4][i % 4]) + "]" + ((i + 1) % 4 == 0 ? '\n' : ' '));
            return s;
        }

    protected:

    private:
        float m_matrix[4][4];
};

#endif // MATH3D_H
