/**
 * IGRA Assignment 1: Smiley Editor
 * Completed by Brandon Gui (1828865) from DIT/FT/2B05.
 */

#pragma once

#ifndef SMILEY_H
#define SMILEY_H

#include "Vector2f.h"   // for positions
#include "Color3f.h"    // for colour values
#include "Color4f.h"    // for colour values, but with transparency support as well

#include "framework.h"  // for WPARAM

class Smiley
{
private:
    
    Vector2f position;
    float radius;
    bool isSelected{false};

    float minRadius{20.f / 400.f};
    float maxRadius{400.f / 400.f};

    Vector2f cursorPositionWhenSelected{};      // The position of the cursor when it is selected
    Vector2f positionDiffFromCursorAndSmiley{};  // The position difference between the cursor and the Smiley. Prevents Smiley from jumping around during movement
    float initialRadiusWhenSelected{};           // The radius of the smiley when it is selected
    bool isCursorInside{false};                 // Whether or not the cursor is inside the smiley
    bool radiusClamped{false};                  // Whether the radius has been clamped because it is too big or too small.

    Color3f colorWhenUnselected{Color3f(0, 0, 1)};  // The color of the Smiley when it isn't selected.
    Color3f colorWhenSelected{Color3f(1, 0, 0)};    // The color of the Smiley when it is selected.

    Vector2f eyePosition{};  // The coordinates where the eyes are positioned.
    float eyeRadius{};        // The size of the eyes.
    float eyeDistanceApart{}; // The distance between the eyes.

    float mouthSize{};        // How wide will the mouth be

public:
    
    /// <summary>Constructs a Smiley with the specified position and radius, in OpenGL coordinates.</summary>
    Smiley(const Vector2f &position, float radius);
    
    void Select();
    void Deselect();

    bool GetIsSelected() const;

    Vector2f GetPosition() const;
    float GetRadius() const;

private:

    // Draws an arc which starts at a specified start angle and ends at a specified end angle.
    // position - the position of the arc. This is relative to the centre.
    // radius - how big and far will the arc be from the center
    // startAngle - the angle to start the arc
    // endAngle - the angle to end the arc
    // arcColour - the colour of the arc
    // resolution - determines the accuracy of the arc. Higher resolution results in rounder arcs
    void DrawArc(const Vector2f &position, float radius, float startAngle, float endAngle, const Color3f &arcColor, int resolution = 32) const;

    /// <summary>
    /// Draws a circle at the specified position with a given radius and circle colour.
    /// The resolution of the circle changes how round the circle will appear.
    /// </summary>
    void DrawCircle(const Vector2f &position, float radius, const Color4f &circleColor, bool colorOutline, int resolution = 64) const;

    /// <summary> Draws the face of the smiley.</summary>
    void DrawFace(const Vector2f &position, float radius, const Color4f &faceOutlineColor, int resolution = 64) const;

    /// <summary> Draws the eyes of the smiley at the position, with a specified distance apart.</summary>
    void DrawEyes(const Vector2f &position, float eyeRadius, float distanceApart, const Color4f &eyeColor) const;

    /// <summary>
    /// Draws the mouth of the smiley at the specified position with the specified distance, and whether to
    /// flip it around.
    /// </summary>
    void DrawMouth(const Vector2f &position, float radius, bool upsideDown, const Color3f &mouthColor) const;

    /// <summary>Returns a boolean based on whether the mouse cursor is inside the smiley.</summary>
    bool IsCursorInside(const Vector2f &openGL_mousePosition) const;
    
    ///// Callback Functions (private scope) /////

    /// <summary>Called when the Smiley is resized.</summary>
    void OnResize();

public:
    ///// Callback Functions /////

    /// <summary>Callback function that draws the smiley when called.</summary>
    void Draw();

    /// <summary>Callback function that gets called when the left mouse button is pressed down.</summary>
    bool OnLMouseButtonDown(const Vector2f &openGL_mousePosition);

    /// <summary>Callback function that gets called when the mouse is moved.</summary>
    void OnMouseMove(const Vector2f &openGL_mousePosition, const WPARAM &wParam);

    /// <summary>Callback function that gets called when the control key is pressed down.</summary>
    void OnCtrlKeyDown(const Vector2f &openGL_mousePosition);

    /// <summary>Callback function that gets called when the control key is released.</summary>
    void OnCtrlKeyUp(const Vector2f &openGL_mousePosition);
};

#endif