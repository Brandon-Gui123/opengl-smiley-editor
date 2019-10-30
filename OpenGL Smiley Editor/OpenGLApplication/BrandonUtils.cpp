#include "BrandonUtils.h"
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
