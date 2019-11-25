#pragma once

#ifndef POOF_PARTICLES_H
#define POOF_PARTICLES_H

#include "Color4f.h"    // for colour
#include "Vector2f.h"   // for positions

class PoofParticles
{
private:
    Vector2f position;          // The current position of the poof particles.
    float innerRadius;          // How far will the start of the poof particle line be away from its center.
    float outerRadius;          // How far the end of the poof particle line be away from its center.
    int numLines;               // How many lines to draw for the poof particles.
    Color4f lineColor;          // The color of the poof particle lines.

    float currentInnerRadius;   // The current inner radius of the particle lines.
    float currentOuterRadius;   // The current outer radius of the particle lines.
    bool shown{false};          // Whether the poof particles are being shown on-screen.

    int activeTime{250};
    int currentTime{0};
    float progress{0};

public:
    
    PoofParticles();
    PoofParticles(const Vector2f &position, float innerRadius, float outerRadius, int numLines);

    bool IsShown() const;
    void SetShown(bool newShown);

    void SetPosition(const Vector2f &newPosition);

    void SetInnerRadius(float newInnerRadius);

    void SetOuterRadius(float newOuterRadius);

    void SetLineColor(const Color4f &newLineColor);

    void ResetAnimation();

    void Draw();

    void Progress(int deltaTime);
};

#endif