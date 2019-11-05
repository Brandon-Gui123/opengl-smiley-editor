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
    
    /// <summary>Gets the length of this vector.</summary>
    float getMagnitude();

    /// <summary>
    /// Gets the square of the length of this vector. 
    /// Use this if you're just comparing distances since this is faster due to the lack of the square root function.
    /// </summary>
    float getSqrMagnitude();

    /// <summary>Sets the coordinates in the current Vector2f object to the new ones specified.</summary>
    void set(float newX, float newY);

    /// Operator Overloads ///
    // This operator is overloaded using a member function
    // Because this is a member function, you have access to "this".
    // The return type can be void, but if we did it that way, we can no longer chain operators (e.g. a + b += c)
    /// <summary>Adds a the vector on the right to the vector on the left of this operand.</summary>
    Vector2f operator+=(Vector2f addend);

    /// <summary>Subtracts the vector on the left of this operand with the one on the right.</summary>
    Vector2f operator-=(Vector2f minuend);

    /// <summary>Multiplies the vector on the left of this operand with the float on the right</summary>
    Vector2f operator*=(float multiplier);

    /// <summary>Divides the vector on the left of this operand with the float on the right.</summary>
    Vector2f operator/=(float divisor);
};

/// <summary>Returns a vector that has the sum of the x and y values from the provided 2 vectors</summary>
Vector2f operator+(const Vector2f &first, const Vector2f &second);

/// <summary>Returns a vector that has the difference between the x and y values from the provided 2 vectors</summary>
Vector2f operator-(const Vector2f &first, const Vector2f &second);

/// <summary>Returns a vector that has all of its values multiplied by the specified multiplier</summary>
Vector2f operator*(const Vector2f &vector, float multiplier);

/// <summary>Returns a vector that has all of its values multiplied by the specified multiplier</summary>
Vector2f operator*(float multiplier, const Vector2f &vector);

/// <summary>Returns a vector that has all of its values divided by the specified multiplier</summary>
Vector2f operator/(const Vector2f &vector, float divisor);

#endif