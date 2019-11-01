#pragma once

#ifndef SMILEY_H
#define SMILEY_H

#include "Vector2f.h"   // for positions
#include "Color3f.h"    // for colour values

class Smiley
{
public:

    Vector2f position;
    float radius;

    Smiley(Vector2f position, float radius);

private:

    // Draws an arc which starts at a specified start angle and ends at a specified end angle.
    // position - the position of the arc. This is relative to the centre.
    // radius - how big and far will the arc be from the center
    // startAngle - the angle to start the arc
    // endAngle - the angle to end the arc
    // arcColour - the colour of the arc
    // resolution - determines the accuracy of the arc. Higher resolution results in rounder arcs
    void DrawArc(Vector2f position, float radius, float startAngle, float endAngle, Color3f arcColor, int resolution = 20);

    /// <summary>
    /// Draws a circle at the specified position with a given radius and circle colour.
    /// The resolution of the circle changes how round the circle will appear.
    /// </summary>
    void DrawCircle(Vector2f position, float radius, Color3f circleColor, int resolution = 20);

    /// <summary> Draws the eyes of the smiley at the position, with a specified distance apart.</summary>
    void DrawEyes(Vector2f position, float eyeRadius, float distanceApart);

    /// <summary>
    /// Draws the mouth of the smiley at the specified position with the specified distance, and whether to
    /// flip it around.
    /// </summary>
    void DrawMouth(Vector2f position, float radius, bool upsideDown);

public:
    /// Callback Functions ///

    /// <summary>Callback function that draws the smiley.</summary>
    void Draw();
};

#endif