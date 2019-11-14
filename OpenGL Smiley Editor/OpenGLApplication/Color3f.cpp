/**
 * IGRA Assignment 1: Smiley Editor
 * Completed by Brandon Gui (1828865) from DIT/FT/2B05.
 */

#include "Color3f.h"

#include "Color4f.h"    // for constructing Color4f instances in implicit conversions

Color3f::Color3f() : red(0.f), green(0.f), blue(0.f)
{}

Color3f::Color3f(float red, float green, float blue) : red(red), green(green), blue(blue)
{}

Color3f::operator Color4f() const
{
    return Color4f(red, green, blue, 1.0f);
}
