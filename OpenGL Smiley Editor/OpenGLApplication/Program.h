/**
 * IGRA Assignment 1: Smiley Editor
 * Completed by Brandon Gui (1828865) from DIT/FT/2B05.
 */

#pragma once

#ifndef PROGRAM_H
#define PROGRAM_H

#include "Vector2f.h"   // for dealing with positions
#include "Smiley.h"     // for accessing the Smiley class

#include <vector>       // for std::vector, which stores Smileys

/// <summary>
/// A class whose purpose is to abstract OpenGL code and provide a centralized way of viewing and executing code.
/// One good example is the Draw method, which handles all the drawing.
/// </summary>
class Program
{
private:

    std::vector<Smiley*> smileyPtrs;
    int smileyCapacity{10};

    HCURSOR hCursor{};

public:

    Program();
    ~Program();

    void DrawGrayAxes();

    void LoadSmileysFromFile();
    void SaveSmileysToFile();

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

    /// <summary>
    /// Called when the "Delete" key is pressed down.
    /// </summary>
    void OnDelKeyDown();

    /// <summary>
    /// Called when the "Ctrl" key is pressed down.
    /// </summary>
    void OnCtrlKeyDown(const Vector2f &openGL_mousePosition);

    /// <summary>
    /// Called when the "Ctrl" key is released.
    /// </summary>
    void OnCtrlKeyUp(const Vector2f &openGL_mousePosition);

    ///// Other Functions /////
};

#endif