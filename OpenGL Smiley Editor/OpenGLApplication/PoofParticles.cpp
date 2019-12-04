#include "PoofParticles.h"

#include "BrandonUtils.h"   // for converting from degrees to radians
#include "Time.h"           // for obtaining delta time

#include "framework.h"      // include file for standard system include files or project specific include files
                            // which also includes the necessary files for drawing OpenGL shapes

#include <cmath>            // for trigonometric functions like sin and cos
#include <gl/GL.h>          // OpenGL 32-bit library

PoofParticles::PoofParticles() : position{Vector2f{0, 0}}, innerRadius{0}, outerRadius{0}, numLines{8}
{
    currentInnerRadius = innerRadius;
    currentOuterRadius = innerRadius;
    lineColor = Color4f{1, 0, 0, 1};
}

PoofParticles::PoofParticles(const Vector2f &position, float innerRadius, float outerRadius, int numLines) : position{position}, innerRadius{innerRadius}, outerRadius{outerRadius}, numLines{numLines}
{
    currentInnerRadius = innerRadius;
    currentOuterRadius = innerRadius;
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

void PoofParticles::ResetAnimation()
{
    currentTime = 0;
    progress = 0;

    currentInnerRadius = innerRadius;
    currentOuterRadius = innerRadius;
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
            glVertex2f(position.x + currentInnerRadius * sin(BrandonUtils::degToRad(step * i)), position.y + currentInnerRadius * cos(BrandonUtils::degToRad(step * i)));
            glVertex2f(position.x + currentOuterRadius * sin(BrandonUtils::degToRad(step * i)), position.y + currentOuterRadius * cos(BrandonUtils::degToRad(step * i)));
        }

    glEnd();
}

void PoofParticles::Update()
{
    // we progress time by adding it to a variable
    currentTime += Time::GetDeltaTime();

    // the progress of the animation is calculated by dividing its current time by its time length
    // giving us a value from 0 to 1
    progress = static_cast<float>(currentTime) / activeTime;

    // we want to see the outer line vertex move out further, then afterwards the inner line vertex will move outwards

    // we want to animate it such that the outer radius will increase first, followed by the inner radius
    if (progress <= 0.5f)
    {
        // so our current outer radius will increase in size until it reaches the specified outer radius
        // divison by 0.5f because by the time it reaches 0.5f, it is done
        currentOuterRadius = innerRadius + ((progress / 0.5f) * (outerRadius - innerRadius));
    }
    else if (progress > 0.5f)
    {
        // and our current inner radius will increase in size until it reaches the specified outer radius
        // minus 0.5f because the progress for this animation is 0, not 0.5f
        currentInnerRadius = innerRadius + (((progress - 0.5f) / 0.5f) * (outerRadius - innerRadius));
    }

    if (currentTime >= activeTime)
    {
        shown = false;
    }
}
