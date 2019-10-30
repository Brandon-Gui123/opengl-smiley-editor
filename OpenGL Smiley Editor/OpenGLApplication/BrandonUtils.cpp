#include "BrandonUtils.h"

// for user-defined mathematical constants, like epsilon
#include "UserDefinedConstants.h"

#include <cmath>    // for fabs(), which returns the positive value for a given number

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
