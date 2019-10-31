#pragma once

#ifndef BRANDON_UTILS_H
#define BRANDON_UTILS_H

#include "Vector2f.h"

/// <summary>
/// A namespace containing commonly-used functionality in this program, such as converting from
/// OpenGL coordinates to Windows coordinates.
/// </summary>
namespace BrandonUtils
{
    /// <summary>Converts a number from an old range to a new range.</summary>
    float map(float current, float oldMin, float oldMax, float newMin, float newMax);

    /// <summary>
    /// Checks if both floats are "close enough" to be equal. The value of "close enough" depends on the value of the floats.
    /// If the floats are huge, "close enough" will be big. And if the floats are small, "close enough" will be very small.
    /// This is Donald Knuth's algorithm on relative epsilons.
    /// </summary>
    bool isApproximatelyEqual(float first, float second);

    /// <summary>
    /// Converts the given vector from window coordinates to OpenGL coordinates, with a specified window size.
    /// </summary>
    Vector2f winCoordsToOpenGL(const Vector2f &winCoords, const Vector2f &winSize);

    /// <summary>
    /// Converts the given vector from OpenGL coordinates to window coordinates, with a specified window size.
    /// </summary>
    Vector2f openGLCoordsToWindows(const Vector2f &openGLCoords, const Vector2f &winSize);
}

#endif