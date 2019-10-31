#include "BrandonUtils.h"

// for user-defined consants, like the epsilon
#include "UserDefinedConstants.h"

#define _USE_MATH_DEFINES   // for using mathematical constants defined in the math library
#include <cmath>            // for mathematical functions like sin, cos and fabs

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

bool BrandonUtils::isApproximatelyEqual(float first, float second)
{
    // since relative epsilon comparison fails when numbers approach closer to zero,
    // we will first check using an absolute epsilon
    if (fabs(first - second) <= USER_DEFINED_MATH_EPSILON)
    {
        return true;
    }

    // otherwise, fallback to Knuth's algorithm for relative epsilon

    // select the larger value among the two floats
    float largerValue = (fabs(first) < fabs(second)) ? fabs(second) : fabs(first);

    // calculate the relative epsilon because the absolute epsilon is too big for 
    // extremely small values (values smaller than the epsilon) and too small for
    // huge values (values way way larger than the epsilon, like 10,000, making 10,000.001 not equal to 10,000)
    // so we need to pick a good epsilon for comparison
    // here, the epsilon is a percentage, and we use it to ask if
    // the smaller float is within the "epsilon" percentage of the larger float
    float relativeEpsilon = largerValue * USER_DEFINED_MATH_EPSILON;

    return fabs(first - second) <= relativeEpsilon;
}

Vector2f BrandonUtils::winCoordsToOpenGL(const Vector2f &winCoords, const Vector2f &winSize)
{
    return Vector2f(map(winCoords.x, 0, winSize.x, -1, 1), map(winCoords.y, 0, winSize.y, 1, -1));
}

Vector2f BrandonUtils::openGLCoordsToWindows(const Vector2f &openGLCoords, const Vector2f &winSize)
{
    return Vector2f(map(openGLCoords.x, -1, 1, 0, winSize.x), map(openGLCoords.y, 1, -1, 0, winSize.y));
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
