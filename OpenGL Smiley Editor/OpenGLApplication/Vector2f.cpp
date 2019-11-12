/**
 * IGRA Assignment 1: Smiley Editor
 * Completed by Brandon Gui (1828865) from DIT/FT/2B05.
 */

#include "Vector2f.h"

#include <cmath>    // for sqrtf, which finds the square root of a float

Vector2f::Vector2f() : x(0.f), y(0.f)
{}

Vector2f::Vector2f(float x, float y) : x(x), y(y)
{}

float Vector2f::getMagnitude() const
{
    return sqrtf(x * x + y * y);
}

float Vector2f::getSqrMagnitude() const
{
    return x * x + y * y;
}

void Vector2f::set(float newX, float newY)
{
    x = newX;
    y = newY;
}

Vector2f operator+(const Vector2f &first, const Vector2f &second)
{
    return Vector2f(first.x + second.x, first.y + second.y);
}

Vector2f operator-(const Vector2f &first, const Vector2f &second)
{
    return Vector2f(first.x - second.x, first.y - second.y);
}

Vector2f operator*(const Vector2f &vector, float multiplier)
{
    return Vector2f(vector.x * multiplier, vector.y * multiplier);
}

Vector2f operator*(float multiplier, const Vector2f &vector)
{
    return Vector2f(multiplier * vector.x, multiplier * vector.y);
}

Vector2f operator/(const Vector2f &vector, float divider)
{
    return Vector2f(vector.x / divider, vector.y / divider);
}

Vector2f Vector2f::operator+=(const Vector2f &addend)
{
    this->x += addend.x;
    this->y += addend.y;
    return Vector2f(this->x, this->y);
}

Vector2f Vector2f::operator-=(const Vector2f &minuend)
{
    this->x -= minuend.x;
    this->y -= minuend.y;
    return Vector2f(this->x, this->y);
}

Vector2f Vector2f::operator*=(float multiplier)
{
    this->x *= multiplier;
    this->y *= multiplier;
    return Vector2f(this->x, this->y);
}

Vector2f Vector2f::operator/=(float divisor)
{
    this->x /= divisor;
    this->y /= divisor;
    return Vector2f(this->x, this->y);
}
