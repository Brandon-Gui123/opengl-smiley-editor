#pragma once

#ifndef COLOR3F_H
#define COLOR3F_H

/// <summary>A compact class consisting of red, green and blue values to represent colours.</summary>
class Color3f
{
public:
    float red;
    float green;
    float blue;

public:
    
    /// <summary>Constructs a Color3f that is initialized as black (all of its member variables are initialized to 0)</summary>
    Color3f();

    /// <summary>Constructs a Color3f with a specified red, blue and green value</summary>
    Color3f(float red, float green, float blue);

};

#endif