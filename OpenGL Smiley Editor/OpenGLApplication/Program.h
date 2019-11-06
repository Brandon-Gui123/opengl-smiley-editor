#pragma once

#ifndef PROGRAM_H
#define PROGRAM_H

#include "Vector2f.h"   // for dealing with positions
#include "framework.h"  // for WPARAM type
#include "Smiley.h"     // for accessing the Smiley class

#include <vector>       // for std::vector, which stores Smileys

class Program
{
private:

    int smileyCapacity = 5;
    std::vector<Smiley*> smileyPtrs;

public:

    Program();
    ~Program();

    void DrawGrayAxes();

public:
    ///// Callback Functions /////

    /// <summary>Called when the scene is to be drawn.</summary>
    void Draw();

    /// <summary>
    /// Called when the mouse is moved in the OpenGL space (the area right below the title bar).
    /// The wParam parameter contains more info about the mouse move, such as whether a certain
    /// key is pressed down during the mouse move.
    /// </summary>
    void OnMouseMove(const Vector2f &openGL_mousePos, const WPARAM &wParam);

    /// <summary>Called when the left mouse button is pressed down while the mouse cursor is within the window space.</summary>
    void OnLMouseButtonDown(const Vector2f &openGL_mousePos);

    /// <summary>Called when the right mouse button is pressed down while the mouse cursor is within the window space.</summary>
    void OnRMouseButtonDown(const Vector2f &openGL_mousePos);
};

#endif