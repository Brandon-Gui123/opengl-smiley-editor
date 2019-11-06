#include "Smiley.h"

#include "framework.h"      // for including Windows API to draw in the window (methods like glBegin, glEnd, glVertex2f)
#include "BrandonUtils.h"   // for converting from degrees to radians
#include "Vector2f.h"       // for positions
#include "Color3f.h"        // for colours

#include <gl/GL.h>          // OpenGL 32-bit library
#include <gl/GLU.h>         // GLU 32-bit library
#include <cmath>            // for math functions like sin and cos

Smiley::Smiley(Vector2f position, float radius) : position(position), radius(radius)
{
    // calculate values that alter the eyes and mouth, which are relative to the radius of the smiley
    eyePosition = Vector2f(0, radius * 0.25f);
    eyeRadius = radius * 0.1875f;
    eyeDistanceApart = radius * 0.75f;
    mouthSize = radius * 0.625f;
void Smiley::Select()
{
    isSelected = true;
}

void Smiley::Deselect()
{
    isSelected = false;
}

bool Smiley::GetIsSelected()
{
    return isSelected;
}

///// Drawing Methods /////

void Smiley::DrawArc(Vector2f position, float radius, float startAngle, float endAngle, Color3f arcColor, int resolution)
{
    // we will be placing a new vertex at every "step"
    float step{360.f / resolution};
    
    float currentAngle{startAngle};

    // for cases where the start angle is more than the end angle, we add 360 degrees so that the function can keep drawing over 360
    float correctedEndAngle{(startAngle > endAngle) ? endAngle + 360.f : endAngle};

    glColor3f(arcColor.red, arcColor.green, arcColor.blue);
    glBegin(GL_LINE_STRIP);

        // begin with a vertex at the start angle (we do this so that we can close the arc if it becomes 360)
        glVertex2f(position.x + radius * sin(BrandonUtils::degToRad(currentAngle)), position.y + radius * cos(BrandonUtils::degToRad(currentAngle)));

        while (currentAngle < correctedEndAngle)
        {
            // increase angle to move on to the next position to place the vertex
            // if the value of current angle is more than the "step", we place a vertex at the end angle, ensuring that our arc spans from startAngle to endAngle
            currentAngle += (correctedEndAngle - currentAngle < step) ? correctedEndAngle - currentAngle : step;

            // OpenGL uses radians, so we convert from degrees to radians
            // We then convert from polar coordinates to cartesian coordinates
            // and finally, place the vertex
            // also, note that our position variable is relative to the center of the circle
            glVertex2f(position.x + radius * sin(BrandonUtils::degToRad(currentAngle)), position.y + radius * cos(BrandonUtils::degToRad(currentAngle)));
        }

    glEnd();
}

void Smiley::DrawCircle(Vector2f position, float radius, Color3f circleColour, bool colorOutline, int resolution)
{
    // a new vertex will be placed at every "step"
    float step{360.f / resolution};
    
    // drawing the outline of the circle
    glColor3f(circleColour.red, circleColour.green, circleColour.blue);
    glBegin(colorOutline ? GL_LINE_LOOP : GL_POLYGON);
        
        for (int i{0}; i < resolution; i++)
        {
            // convert from degrees to radians, convert from polar coordinates to cartesian coordinates,
            // then place the vertex down relative to the specified position
            glVertex2f(position.x + radius * sin(BrandonUtils::degToRad(step * i)), position.y + radius * cos(BrandonUtils::degToRad(step * i)));
        }

    glEnd();
}

void Smiley::DrawFace(Vector2f position, float radius, Color3f faceOutlineColor, int resolution)
{
    // draws a circle filled with white colour acting as the base
    DrawCircle(position, radius, Color3f(1.f, 1.f, 1.f), false, resolution);

    // draws an outline of the circle
    DrawCircle(position, radius, faceOutlineColor, true, resolution);
}

void Smiley::DrawEyes(Vector2f position, float eyeRadius, float distanceApart, Color3f eyeColor)
{
    DrawCircle(Vector2f(position.x - distanceApart / 2, position.y), eyeRadius, eyeColor, true);  // left eye
    DrawCircle(Vector2f(position.x + distanceApart / 2, position.y), eyeRadius, eyeColor, true);  // right eye
}

void Smiley::DrawMouth(Vector2f position, float radius, bool upsideDown, Color3f mouthColor)
{
    if (upsideDown)
    {
        // note that drawing the arcs upside down require us to re-position it so that it looks like it is still in the same place
        // since this is the upper part of the circle
        DrawArc(position - Vector2f(0, radius * 1.5f), radius, 300, 60, mouthColor);
    }
    else
    {
        DrawArc(position, radius, 120, 240, mouthColor);
    }
}

bool Smiley::IsCursorInside(const Vector2f &openGL_mousePosition)
{
    return (openGL_mousePosition - position).getSqrMagnitude() < radius * radius;
}

void Smiley::OnResize()
{
    // recalculate all the vectors and floats that position the eyes and mouth
    // we place this all here so that we don't have to calculate them on every Draw call
    // but calculate them every time our smiley changes in size
    eyePosition.set(0, radius * 0.25f);
    eyeRadius = radius * 0.1875f;
    eyeDistanceApart = radius * 0.75f;
    mouthSize = radius * 0.625f;
}

void Smiley::Draw()
{
    Color3f smileyColor { isSelected ? colorWhenSelected : colorWhenUnselected };

    // the face of the smiley
    DrawFace(position, radius, smileyColor);

    // the eyes of the smiley
    DrawEyes(position + eyePosition, eyeRadius, eyeDistanceApart, smileyColor);

    // the mouth
    DrawMouth(position, mouthSize, !isSelected, smileyColor);
}

bool Smiley::OnLMouseButtonDown(const Vector2f &openGL_mousePosition)
{
    isSelected = IsCursorInside(openGL_mousePosition);
    
    if (isSelected)
    {
        // keep track of the current radius of the smiley during the mouse click so we can resize it properly
        // when the user holds down the ctrl key moves the mouse
        initialRadiusWhenSelected = radius;

        // keep track of the position of the cursor when the Smiley is clicked
        // this would help prevent incorrect radius scaling due to distance from origin of the OpenGL space
        cursorPositionWhenSelected = openGL_mousePosition;
    }

    return isSelected;
}

void Smiley::OnMouseMove(const Vector2f &openGL_mousePosition, const WPARAM &wParam)
{
    if (isSelected)
    {
        // if the ctrl key and the left mouse button is held down
        if ((wParam & (MK_CONTROL | MK_LBUTTON)) == ((MK_CONTROL | MK_LBUTTON)))
        {
            // calculate the new radius of the smiley from the adjustment
            float newRadius{initialRadiusWhenSelected + openGL_mousePosition.x - cursorPositionWhenSelected.x};

            // clamp the radius of the smiley to prevent it from becoming too big or too small
            if (newRadius < minRadius)
            { 
                radius = minRadius;
                
                // call OnResize if the radius has changed and is now minRadius
                if (!radiusClamped) OnResize();

                // prevent further calling the OnResize function
                radiusClamped = true;
            }
            else if (newRadius > maxRadius)
            { 
                radius = maxRadius;

                // call OnResize if the radius has changed and is now minRadius
                if (!radiusClamped) OnResize();

                // prevent further calling the OnResize function
                radiusClamped = true;
            }
            else
            {
                radius = newRadius;
                OnResize();
                radiusClamped = false;
            }
        }
    }
}
