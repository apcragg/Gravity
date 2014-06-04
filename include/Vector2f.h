#ifndef VECTOR2F_H
#define VECTOR2F_H

#include <math.h>
#include <sstream>


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

        virtual ~Vector2f();
    protected:
    private:
        float x, y;
};

#endif // VECTOR2F_H
