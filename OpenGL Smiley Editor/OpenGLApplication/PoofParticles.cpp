#include "PoofParticles.h"

#include "BrandonUtils.h"   // for converting from degrees to radians

#include "framework.h"      // include file for standard system include files or project specific include files
                            // which also includes the necessary files for drawing OpenGL shapes

#include <cmath>            // for trigonometric functions like sin and cos
#include <gl/GL.h>          // OpenGL 32-bit library


PoofParticles::PoofParticles() : position(Vector2f{0, 0}), innerRadius(0), outerRadius(0), numLines(8)
{
    currentInnerRadius = 0;
    currentOuterRadius = 0;
    lineColor = Color4f{1, 0, 0, 1};
}

PoofParticles::PoofParticles(const Vector2f &position, float innerRadius, float outerRadius, int numLines) : position(position), innerRadius(innerRadius), outerRadius(outerRadius), numLines(numLines)
{
    currentInnerRadius = 0;
    currentOuterRadius = 0;
    lineColor = Color4f{1, 0, 0, 1};
}

bool PoofParticles::IsShown() const
{
    return shown;
}

void PoofParticles::SetShown(bool newShown)
{
    shown = newShown;
}

void PoofParticles::SetPosition(const Vector2f & newPosition)
{
    position = newPosition;
}

void PoofParticles::SetInnerRadius(float newInnerRadius)
{
    innerRadius = newInnerRadius;
}

void PoofParticles::SetOuterRadius(float newOuterRadius)
{
    outerRadius = newOuterRadius;
}

void PoofParticles::SetLineColor(const Color4f &newLineColor)
{
    lineColor = newLineColor;
}

void PoofParticles::ResetTimer()
{
    currentTime = 0;
}

void PoofParticles::Draw()
{
    if (!shown) return;

    // a new line will be placed at every "step"
    float step{360.f / numLines};

    // drawing the poof particles
    glBegin(GL_LINES);
        glColor4f(lineColor.red, lineColor.green, lineColor.blue, lineColor.alpha);

        for (int i{0}; i < numLines; ++i)
        {
            // draw one closer to the center, then one further away
            glVertex2f(position.x + innerRadius * sin(BrandonUtils::degToRad(step * i)), position.y + innerRadius * cos(BrandonUtils::degToRad(step * i)));
            glVertex2f(position.x + outerRadius * sin(BrandonUtils::degToRad(step * i)), position.y + outerRadius * cos(BrandonUtils::degToRad(step * i)));
        }

    glEnd();
}

void PoofParticles::Progress(int deltaTime)
{
    currentTime += deltaTime;

    if (currentTime >= activeTime)
    {
        shown = false;
        ResetTimer();
    }
}
