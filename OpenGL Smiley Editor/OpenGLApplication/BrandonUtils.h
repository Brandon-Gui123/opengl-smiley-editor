/**
 * IGRA Assignment 1: Smiley Editor
 * Completed by Brandon Gui (1828865) from DIT/FT/2B05.
 */

#pragma once

#ifndef BRANDON_UTILS_H
#define BRANDON_UTILS_H

#include "Vector2f.h"   // for storing coordinates

/// <summary>
/// A namespace containing commonly-used functionality in this program, such as converting from
/// OpenGL coordinates to Windows coordinates.
/// </summary>
namespace BrandonUtils
{
    /// <summary>Converts a number from an old range to a new range.</summary>
    float map(float current, float oldMin, float oldMax, float newMin, float newMax);

    /// <summary>
    /// Converts the given vector from window coordinates to OpenGL coordinates, with a specified window size.
    /// </summary>
    Vector2f winCoordsToOpenGL(const Vector2f &winCoords, const Vector2f &winSize);

    /// <summary>
    /// Converts the given vector from OpenGL coordinates to window coordinates, with a specified window size.
    /// </summary>
    Vector2f openGLCoordsToWindows(const Vector2f &openGLCoords, const Vector2f &winSize);

    /// <summary>Converts the specified degree value to radians.</summary>
    float degToRad(float degrees);

    /// <summary>Converts the specified radian value to degrees.</summary>
    float radToDeg(float radians);
}

#endif