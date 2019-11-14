/**
 * IGRA Assignment 1: Smiley Editor
 * Completed by Brandon Gui (1828865) from DIT/FT/2B05.
 */

#pragma once

#ifndef COLOR4F_H
#define COLOR4F_H

class Color4f
{

public:

    float red;
    float green;
    float blue;
    float alpha;

    Color4f();
    Color4f(float red, float green, float blue, float alpha);
};

#endif