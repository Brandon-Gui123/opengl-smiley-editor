#include "Program.h"

#include "framework.h"  // for including Windows API to draw in the window (methods like glBegin, glEnd, glVertex2f)

#include "Vector2f.h"
#include "BrandonUtils.h"
#include "Smiley.h"

#include <gl/GL.h>  // OpenGL 32-bit library
#include <gl/GLU.h> // GLU 32-bit library

void Program::Draw()
{
    DrawGrayAxes();
    
    // draw all smileys
    for (auto smileyPtrIterator{smileyPtrs.begin()}; smileyPtrIterator != smileyPtrs.end(); smileyPtrIterator++)
    {
        (*smileyPtrIterator)->Draw();
    }
}

Program::Program()
{
    // set the capacity of the smiley vector to be at least the value specified in the variable
    smileyPtrs.reserve(smileyCapacity);

    // initialize one smiley in the program
    smileyPtrs.push_back(new Smiley(Vector2f(0.f, 0.f), 0.25f));
}

Program::~Program()
{
    // iterate through the vector of smiley pointers to deallocate memory used by the Smileys
    // then set its pointer to nullptr to prevent dangling pointers
    for (auto smileyPtrIterator{smileyPtrs.begin()}; smileyPtrIterator != smileyPtrs.end(); smileyPtrIterator++)
    {
        delete (*smileyPtrIterator);
        (*smileyPtrIterator) = nullptr;
    }
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

void Program::OnMouseMove(const Vector2f &openGL_mousePos, const WPARAM &wParam)
{
    // let all smileys process the mouse movement
    for (auto smileyPtrIterator{smileyPtrs.begin()}; smileyPtrIterator != smileyPtrs.end(); smileyPtrIterator++)
    {
        (*smileyPtrIterator)->OnMouseMove(openGL_mousePos, wParam);
    }
}

void Program::OnLMouseButtonDown(const Vector2f &openGL_mousePos)
{
    // let all smileys process the left mouse button down
    for (auto smileyPtrIterator{smileyPtrs.begin()}; smileyPtrIterator != smileyPtrs.end(); smileyPtrIterator++)
    {
        (*smileyPtrIterator)->OnLMouseButtonDown(openGL_mousePos);
    }
}

void Program::OnRMouseButtonDown(const Vector2f & openGL_mousePos)
{}
