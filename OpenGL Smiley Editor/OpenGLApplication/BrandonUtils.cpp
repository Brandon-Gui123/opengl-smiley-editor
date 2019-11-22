/**
 * IGRA Assignment 1: Smiley Editor
 * Completed by Brandon Gui (1828865) from DIT/FT/2B05.
 */

#include "BrandonUtils.h"

#include "UserDefinedConstants.h"   // for constants that I have defined, like epsilon

#define _USE_MATH_DEFINES           // for using mathematical constants defined in the math library. 
                                    // This has to be defined before including the cmath library.

#include <cmath>                    // for mathematical functions like sin, cos and fabs

float BrandonUtils::map(float current, float oldMin, float oldMax, float newMin, float newMax)
{
    // TODO: Overflow check?
    // first, we map the current value from range [oldMin, oldMax] to [0, (oldMax - oldMin)]
    // here, we are just shifting the range
    // but then, we also need to shift our current value
    // float shiftedCurrent = current - oldMin;

    // now, we map from range [0, (oldMax - oldMin)] to range [0, (newMax - newMin)]
    // the new range can be calculated by shifting the range
    // using our new range, we map the shifted current value using it
    // float mapped_shiftedCurrent = (shiftedCurrent / (oldMax - oldMin)) * (newMax - newMin)

    // finally, we shift back the new range from [0, (newMax - newMin)] to [newMin, newMax]
    // to accomodate that, we shift our current value
    // and we will have our result
    // float shifted_mapped_shiftedCurrent = mapped_shiftedCurrent + newMin;
    // return shifted_mapped_shiftedCurrent;

    // the following statement combines all of the above into one expression
    return (((current - oldMin) / (oldMax - oldMin)) * (newMax - newMin)) + newMin;
}

Vector2f BrandonUtils::winCoordsToOpenGL(const Vector2f &winCoords, const Vector2f &winSize)
{
    return Vector2f{map(winCoords.x, 0, winSize.x, -1, 1), map(winCoords.y, 0, winSize.y, 1, -1)};
}

Vector2f BrandonUtils::openGLCoordsToWindows(const Vector2f &openGLCoords, const Vector2f &winSize)
{
    return Vector2f{map(openGLCoords.x, -1, 1, 0, winSize.x), map(openGLCoords.y, 1, -1, 0, winSize.y)};
}

float BrandonUtils::degToRad(float degrees)
{
    // 180 degrees is PI radians
    // 1 degree is therefore PI / 180 radians
    return degrees * (M_PI / 180);
}

float BrandonUtils::radToDeg(float radians)
{
    // PI radians is 180 degrees
    // 1 radian is therefore 180 / PI degrees
    return radians * (180 / M_PI);
}
