/**
 * IGRA Assignment 1: Smiley Editor
 * Completed by Brandon Gui (1828865) from DIT/FT/2B05.
 */

#include "Smiley.h"

#include "BrandonUtils.h"   // for converting from degrees to radians
#include "Color3f.h"        // for colours
#include "Color4f.h"        // for colours, with transparency support
#include "Vector2f.h"       // for positions

#include "framework.h"      // include file for standard system include files or project specific include files
                            // which also includes the necessary files for drawing OpenGL shapes

#include <cmath>            // for math functions like sin and cos
#include <gl/GL.h>          // OpenGL 32-bit library
#include <gl/GLU.h>         // GLU 32-bit library

Smiley::Smiley(const Vector2f &position, float radius) : position{position}, radius{radius}
{
    // calculate values that alter the eyes and mouth, which are relative to the radius of the smiley
    eyePosition = Vector2f{0, radius * 0.25f};
    eyeRadius = radius * 0.1875f;
    eyeDistanceApart = radius * 0.75f;
    mouthSize = radius * 0.625f;
    currentColor = colorWhenUnselected;
}

void Smiley::Select()
{
    isSelected = true;
    currentColor = colorWhenSelected;
}

void Smiley::Deselect()
{
    isSelected = false;
    currentColor = colorWhenUnselected;
}

bool Smiley::GetIsSelected() const
{
    return isSelected;
}

Vector2f Smiley::GetPosition() const
{
    return position;
}

float Smiley::GetRadius() const
{
    return radius;
}

Color3f Smiley::GetColor() const
{
    return currentColor;
}

///// Drawing Methods /////

void Smiley::DrawArc(const Vector2f &position, float radius, float startAngle, float endAngle, const Color3f &arcColor, int resolution) const
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

void Smiley::DrawCircle(const Vector2f &position, float radius, const Color4f &circleColour, bool colorOutline, int resolution) const
{
    // a new vertex will be placed at every "step"
    float step{360.f / resolution};
    
    // drawing the outline of the circle
    glColor4f(circleColour.red, circleColour.green, circleColour.blue, circleColour.alpha);
    glBegin(colorOutline ? GL_LINE_LOOP : GL_POLYGON);
        
        for (int i{0}; i < resolution; ++i)
        {
            // convert from degrees to radians, convert from polar coordinates to cartesian coordinates,
            // then place the vertex down relative to the specified position
            glVertex2f(position.x + radius * sin(BrandonUtils::degToRad(step * i)), position.y + radius * cos(BrandonUtils::degToRad(step * i)));
        }

    glEnd();
}

void Smiley::DrawFace(const Vector2f &position, float radius, const Color4f &faceOutlineColor, int resolution) const
{
    // draws a circle filled with white colour acting as the base
    DrawCircle(position, radius, Color4f{1.f, 1.f, 1.f, 1.f}, false, resolution);

    // draws an outline of the circle
    DrawCircle(position, radius, faceOutlineColor, true, resolution);
}

void Smiley::DrawEyes(const Vector2f &position, float eyeRadius, float distanceApart, const Color4f &eyeColor) const
{
    DrawCircle(Vector2f{position.x - distanceApart / 2, position.y}, eyeRadius, eyeColor, true);  // left eye
    DrawCircle(Vector2f{position.x + distanceApart / 2, position.y}, eyeRadius, eyeColor, true);  // right eye
}

void Smiley::DrawMouth(const Vector2f &position, float radius, bool upsideDown, const Color3f &mouthColor) const
{
    if (upsideDown)
    {
        // note that drawing the arcs upside down require us to re-position it so that it looks like it is still in the same place
        // since this is the upper part of the circle
        DrawArc(position - Vector2f{0, radius * 1.5f}, radius, 300, 60, mouthColor);
    }
    else
    {
        DrawArc(position, radius, 120, 240, mouthColor);
    }
}

bool Smiley::IsCursorInside(const Vector2f &openGL_mousePosition) const
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
    // the shadow of the smiley
    DrawCircle(position + Vector2f{0.025f, -0.025f}, radius, Color4f{0, 0, 0, 0.4f}, false);

    // the face of the smiley
    DrawFace(position, radius, currentColor);

    // the eyes of the smiley
    DrawEyes(position + eyePosition, eyeRadius, eyeDistanceApart, currentColor);

    // the mouth
    DrawMouth(position, mouthSize, !isSelected, Color3f(currentColor.red, currentColor.green, currentColor.blue));
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

        // calculate the vector that points from the cursor to the smiley's position
        positionDiffFromCursorAndSmiley = position - openGL_mousePosition;
    }

    currentColor = isSelected ? colorWhenSelected : colorWhenUnselected;

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
        else if (wParam & MK_LBUTTON)
        {
            // you can think of this as moving the center of the smiley to the cursor's position
            // but then moving it again based on the position difference between the cursor's position
            // and the smiley's position
            position = openGL_mousePosition + positionDiffFromCursorAndSmiley;
        }
    }
}

void Smiley::OnCtrlKeyDown(const Vector2f &openGL_mousePosition)
{
    if (isSelected)
    {
        // keep track of the current radius of the smiley during the mouse click so we can resize it properly
        // when the user holds down the ctrl key moves the mouse
        initialRadiusWhenSelected = radius;

        // keep track of the position of the cursor when the Smiley is clicked
        // this would help prevent incorrect radius scaling due to distance from origin of the OpenGL space
        cursorPositionWhenSelected = openGL_mousePosition;
    }
}

void Smiley::OnCtrlKeyUp(const Vector2f &openGL_mousePosition)
{
    if (isSelected)
    {
        // keep track of the position of the cursor when the Smiley is clicked
        // this would help prevent incorrect radius scaling due to distance from origin of the OpenGL space
        cursorPositionWhenSelected = openGL_mousePosition;

        // calculate the vector that points from the cursor to the smiley's position
        positionDiffFromCursorAndSmiley = position - openGL_mousePosition;
    }
}
