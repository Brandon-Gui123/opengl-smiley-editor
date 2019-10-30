#pragma once

#ifndef VECTOR2F_H
#define VECTOR2F_H

/// <summary>A compact class that stores two float values. It can be used to represent a point in 2D space.</summary>
class Vector2f
{
public:

    float x;
    float y;

public:

    /// <summary>Constructs a Vector2f with its member fields being initialized to 0.</summary>
    Vector2f();

    /// <summary>Constructs a Vector2f with the specified parameters for the x and y values.</summary>
    Vector2f(float x, float y);
    
    // We need to make operators a friend function to access internal variables and to place it as a
    // forward declaration 
    /// <summary>Returns a vector that has the sum of the x and y values from the provided 2 vectors</summary>
    friend Vector2f operator+(const Vector2f &first, const Vector2f &second);

    /// <summary>Returns a vector that has the difference between the x and y values from the provided 2 vectors</summary>
    friend Vector2f operator-(const Vector2f &first, const Vector2f &second);

    /// <summary>Returns a vector that has all of its values multiplied by the specified multiplier</summary>
    friend Vector2f operator*(const Vector2f &vector, float multiplier);

    /// <summary>Returns a vector that has all of its values multiplied by the specified multiplier</summary>
    friend Vector2f operator*(float multiplier, const Vector2f &vector);

    /// <summary>Returns a vector that has all of its values divided by the specified multiplier</summary>
    friend Vector2f operator/(const Vector2f &vector, float divisor);
#endif