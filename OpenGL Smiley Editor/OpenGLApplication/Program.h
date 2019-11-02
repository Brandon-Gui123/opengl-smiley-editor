#pragma once

#ifndef PROGRAM_H
#define PROGRAM_H

#include "Vector2f.h"

class Program
{
public:
    void DrawGrayAxes();

public:
    /// Callback Functions ///

    /// <summary>Called when the scene is to be drawn.</summary>
    void Draw();

    /// <summary>Called when the mouse is moved in the OpenGL space (the area right below the title bar).</summary>
    void OnMouseMove(const Vector2f &openGL_mousePos);

    /// <summary>Called when the left mouse button is pressed down while the mouse cursor is within the window space.</summary>
    void OnLMouseButtonDown(const Vector2f &openGL_mousePos);

    /// <summary>Called when the right mouse button is pressed down while the mouse cursor is within the window space.</summary>
    void OnRMouseButtonDown(const Vector2f &openGL_mousePos);
};

#endif