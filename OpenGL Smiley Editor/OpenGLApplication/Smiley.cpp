#include "Smiley.h"

#include "framework.h"      // for including Windows API to draw in the window (methods like glBegin, glEnd, glVertex2f)
#include "BrandonUtils.h"   // for converting from degrees to radians
#include "Vector2f.h"   // for positions
#include "Color3f.h"    // for colours

#include <gl/GL.h>  // OpenGL 32-bit library
#include <gl/GLU.h> // GLU 32-bit library
#include <cmath>    // for math functions like sin and cos

void Smiley::DrawArc(Vector2f position, float radius, float startAngle, float endAngle, Color3f arcColor, int resolution)
{
    // we will be placing a new vertex at every "step"
    float step = 360.f / resolution;
    
    float currentAngle = startAngle;

    // for cases where the start angle is more than the end angle, we add 360 degrees so that the function can keep drawing over 360
    float correctedEndAngle = (startAngle > endAngle) ? endAngle + 360.f : endAngle;

    glColor3f(arcColor.red, arcColor.green, arcColor.blue);
    glBegin(GL_LINE_STRIP);

        // begin with a vertex at the start angle (we do this so that we can close the arc if it becomes 360)
        glVertex2f(radius * sin(BrandonUtils::degToRad(currentAngle)), radius * cos(BrandonUtils::degToRad(currentAngle)));

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

void Smiley::DrawCircle(Vector2f position, float radius, Color3f circleColor, int resolution)
{
    // a new vertex will be placed at every "step"
    float step = 360.f / resolution;

    glColor3f(circleColor.red, circleColor.green, circleColor.blue);
    glBegin(GL_LINE_LOOP);
        
        for (int i = 0; i < resolution; i++)
        {
            // convert from degrees to radians, convert from polar coordinates to cartesian coordinates,
            // then place the vertex down relative to the specified position
            glVertex2f(position.x + radius * sin(BrandonUtils::degToRad(step * i)), position.y + radius * cos(BrandonUtils::degToRad(step * i)));
        }

    glEnd();
}
