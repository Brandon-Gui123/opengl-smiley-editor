#pragma once

#ifndef BRANDON_UTILS_H
#define BRANDON_UTILS_H

/// <summary>
/// A namespace containing commonly-used functionality in this program, such as converting from
/// OpenGL coordinates to Windows coordinates.
/// </summary>
namespace BrandonUtils
{
    /// <summary>Converts a number from an old range to a new range.</summary>
    float map(float current, float oldMin, float oldMax, float newMin, float newMax);
}

#endif