#include "Vector2f.h"

Vector2f::Vector2f() : x(0.f), y(0.f)
{}

Vector2f::Vector2f(float x, float y) : x(x), y(y)
{}
Vector2f operator+(const Vector2f &first, const Vector2f &second)
{
    return Vector2f(first.x + second.x, first.y + second.y);
}

Vector2f operator-(const Vector2f & first, const Vector2f & second)
{
    return Vector2f(first.x - second.x, first.y - second.y);
}

Vector2f operator*(const Vector2f & vector, float multiplier)
{
    return Vector2f(vector.x * multiplier, vector.y * multiplier);
}

Vector2f operator*(float multiplier, const Vector2f & vector)
{
    return Vector2f(multiplier * vector.x, multiplier * vector.y);
}

Vector2f operator/(const Vector2f & vector, float divider)
{
    return Vector2f(vector.x / divider, vector.y / divider);
}
