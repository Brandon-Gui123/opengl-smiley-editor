#include "Program.h"

#include "framework.h"  // for including Windows API to draw in the window (methods like glBegin, glEnd, glVertex2f)

#include "Vector2f.h"
#include "BrandonUtils.h"
#include "Smiley.h"

#include <gl/GL.h>  // OpenGL 32-bit library
#include <gl/GLU.h> // GLU 32-bit library

Smiley smiley = Smiley(Vector2f(0, 0), 0.25f);

void Program::Draw()
{
    DrawGrayAxes();
    smiley.Draw();
}

void Program::DrawGrayAxes()
{
    glBegin(GL_LINES);  // every 2 vertices creates a line
        // draw the horizontal (x) axis
        glColor3f(0.75f, 0.75f, 0.75f);
        glVertex2f(0, 0);
        glVertex2f(1, 0);

        // draw the vertical (y) axis
        glColor3f(0.75f, 0.75f, 0.75f);
        glVertex2f(0, 0);
        glVertex2f(0, 1);
    glEnd();
}

void Program::OnMouseMove(const Vector2f &openGL_mousePos)
{
}

void Program::OnLMouseButtonDown(const Vector2f &openGL_mousePos)
{

}

void Program::OnRMouseButtonDown(const Vector2f & openGL_mousePos)
{}
