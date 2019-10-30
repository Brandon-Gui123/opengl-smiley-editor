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
    
#endif