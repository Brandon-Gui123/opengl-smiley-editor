/**
 * IGRA Assignment 1: Smiley Editor
 * Completed by Brandon Gui (1828865) from DIT/FT/2B05.
 */

#include "Program.h"

#include "BrandonUtils.h"   // for utilizing useful functions that I have defined
#include "Smiley.h"         // everything related to Smileys
#include "Vector2f.h"       // for storing positions

#include "framework.h"      // include file for standard system include files or project specific include files
                            // which also includes the necessary files for drawing OpenGL shapes

#include <fstream>          // for reading and writing to files
#include <gl/GL.h>          // OpenGL 32-bit library
#include <gl/GLU.h>         // GLU 32-bit library
#include <ios>              // for determing the modes used when writing or reading files
#include <string>           // for std::string
#include <vector>           // for using vector methods

void Program::Draw()
{
    // enables blending of colours in OpenGL
    glEnable(GL_BLEND);

    // specifies how to blend red, green and blue colours, as well as alphas
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    DrawGrayAxes();

    // draw all smileys
    // Smiley*& is a reference to a Smiley pointer
    // we use a reference in this for-each loop to avoid making a copy of the Smiley pointer
    for (Smiley *&smileyPtr : smileyPtrs)
    {
        smileyPtr->Draw();
    }

    // draw all poof particles
    for (PoofParticles &poofParticlesEl : poofParticles)
    {
        poofParticlesEl.Draw();
    }

    // disable blending so that other shapes or colours don't get blended in when we don't want them too
    glDisable(GL_BLEND);
}

Program::Program()
{
    // set the capacity of the smiley vector to be at least the value specified in the variable
    smileyPtrs.reserve(smileyCapacity);

    // set the capacity of the poof particles vector to be the same as the smiley vector
    // this is so that if for some reason we were to delete all Smileys at the same time
    // we won't have to resize the vector
    poofParticles.reserve(smileyCapacity);

    // initialize the poof particles vector
    for (int i{0}; i < poofParticles.capacity(); ++i)
    {
        poofParticles.push_back(PoofParticles{});
    }

    // read smileys from file
    LoadSmileysFromFile();

    // initialize one smiley in the program if there are none loaded
    if (smileyPtrs.size() <= 0)
    {
        // provide a Smiley if there's nothing in the file
        smileyPtrs.push_back(new Smiley{Vector2f{0.f, 0.f}, 0.125f});
    }

    // set cursor to the appropriate icon
    SetCursor(hArrowCursor);
}

Program::~Program()
{
    // iterate through the vector of smiley pointers to deallocate memory used by the Smileys
    // then set its pointer to nullptr to prevent dangling pointers
    // Smiley*& is a reference to a Smiley pointer
    for (Smiley *&smileyPtr : smileyPtrs)
    {
        delete smileyPtr;
        smileyPtr = nullptr;
    }

    // clear the vector to remove the null pointers in the vector
    smileyPtrs.clear();

    // set cursor back to the appropriate icon
    SetCursor(hArrowCursor);
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

void Program::LoadSmileysFromFile()
{
    // ifstream is an input stream that can be read from a file (input from a file, hence, it starts with the letter "i")
    std::ifstream smileyFile_inputStream;

    // open the file
    // will read from file (std::ios::in)
    smileyFile_inputStream.open("smileys.txt", std::ios::in);

    if (smileyFile_inputStream.is_open())
    {
        // TODO: Find and implement a better way to do this, instead of using switch and case

        // how we will intepret the current line of data we receieved from the file
        // we use an integer looping from 0 to 3 which acts like a "mode" for what to do with the data receieved
        int dataInterpretation{0};
        std::string currentLine{};
        
        // for keeping track of values
        float smileyPosX_window{};
        float smileyPosY_window{};
        float smileyRadius_window{};

        while (std::getline(smileyFile_inputStream, currentLine))
        {
            switch (dataInterpretation)
            {
                case 0: // left coordinate value
                    smileyPosX_window = std::stof(currentLine);    // converts string to float
                    break;

                case 1: // top coordinate value
                    smileyPosY_window = std::stof(currentLine);
                    break;

                case 2: // radius of the smiley
                    smileyRadius_window = std::stof(currentLine);
                    break;

                case 3: // separator
                    // method returns 0 if both strings are equal
                    if (currentLine.compare("******") == 0)
                    {
                        // convert values to OpenGL
                        Vector2f smileyPos_openGL{BrandonUtils::winCoordsToOpenGL(Vector2f{smileyPosX_window, smileyPosY_window}, Vector2f{400, 400})};
                        float smileyRadius_openGL{BrandonUtils::map(smileyRadius_window, 0, 400, 0, 1)};

                        // constructs a new Smiley, then push it into the vector
                        // add radius back to the position because the position is for top-left corner
                        smileyPtrs.push_back(new Smiley{smileyPos_openGL + Vector2f{smileyRadius_openGL, -smileyRadius_openGL}, smileyRadius_openGL});
                    }
                    break;
            }

            // prevent the value from going over 4
            dataInterpretation = (dataInterpretation + 1) % 4;
        }
    }

    // notify the OS that we are done with the file
    smileyFile_inputStream.close();
}

void Program::SaveSmileysToFile()
{
    // ofstream is an output stream that can be written to a file (output to a file, hence, it starts with the letter "o")
    std::ofstream smileyFile_outputStream;

    // opens a file called "smileys.txt"
    // will write to the file (std::ios::out), replacing all of its contents with new ones (std::ios::trunc)
    smileyFile_outputStream.open("smileys.txt", std::ios::out | std::ios::trunc);

    for (Smiley *&smileyPtr : smileyPtrs)
    {
        // obtain the radius of the smiley to calculate top-left corner coordinate
        float smileyRadius{smileyPtr->GetRadius()};

        // calculate the window coordinates for the top-left corner of the Smiley
        Vector2f topLeft{BrandonUtils::openGLCoordsToWindows(smileyPtr->GetPosition() + Vector2f{-smileyRadius, smileyRadius}, Vector2f{400, 400})};

        // write coordinates to file
        smileyFile_outputStream << topLeft.x << '\n';    // x-coordinate
        smileyFile_outputStream << topLeft.y << '\n';    // y-coordinate

        // write radius value (in window coordinates) to file
        smileyFile_outputStream << BrandonUtils::map(smileyRadius, 0, 1, 0, 400) << '\n'; // radius

        // separator
        smileyFile_outputStream << "******" << '\n';
    }

    // tell the OS that we're done with the file
    smileyFile_outputStream.close();
}

void Program::OnMouseMove(const Vector2f &openGL_mousePos, const WPARAM &wParam)
{
    // let all smileys process the mouse movement
    for (Smiley *&smileyPtr : smileyPtrs)
    {
        smileyPtr->OnMouseMove(openGL_mousePos, wParam);
    }
}

void Program::OnLMouseButtonDown(const Vector2f &openGL_mousePos)
{
    // let all smileys process the left mouse button down
    // we will start from the end of the vector to the beginning because
    // smileys drawn last will be at the very top
    for (int i{static_cast<int>(smileyPtrs.size()) - 1}; i >= 0; --i)
    {
        bool smileyIsSelected{smileyPtrs.at(i)->OnLMouseButtonDown(openGL_mousePos)};

        if (smileyIsSelected)
        {
            // deselect the Smiley at the end of the vector if it is
            // not the Smiley we just selected and if the size of the vector is
            // greater than 1 so we don't deselect the only Smiley we have if it is selected
            // (for when we only have one Smiley)
            if (smileyPtrs.size() > 1 && i != smileyPtrs.size() - 1)
            {
                smileyPtrs.at(smileyPtrs.size() - 1)->Deselect();
            }

            // we take note of the selected smiley at the current index
            Smiley *selectedSmileyPtr{smileyPtrs.at(i)};

            // we shift all elements after the selected smiley down by one space
            for (int j{i}; j < static_cast<int>(smileyPtrs.size()) - 1; ++j)
            {
                smileyPtrs[j] = smileyPtrs[j + 1];
            }

            smileyPtrs[smileyPtrs.size() - 1] = selectedSmileyPtr;

            // exit the loop
            break;
        }
    }

}

void Program::OnRMouseButtonDown(const Vector2f &openGL_mousePos)
{
    if (smileyPtrs.size() < smileyPtrs.capacity())
    {
        Smiley *newSmiley{new Smiley{openGL_mousePos, 0.125f}};

        // only deselect if we have at least one smiley
        if (smileyPtrs.size() > 0)
        {
            // deselect the smiley at the very end of the vector, because elements at the end are drawn on top
            // of the others
            smileyPtrs.at(smileyPtrs.size() - 1)->Deselect();
        }

        // push the new smiley in
        smileyPtrs.push_back(newSmiley);

        // set the newly-created smiley to be the active one
        newSmiley->Select();
    }
    else
    {
        // prohibit adding of smiley and play the default system sound
        MessageBeep(MB_OK);
    }
}

void Program::OnDelKeyDown()
{
    // deletion permitted if there is at least one Smiley
    if (smileyPtrs.size() > 0)
    {
        // get the Smiley pointer at the end of the vector
        Smiley *lastSmileyPtr{smileyPtrs.at(smileyPtrs.size() - 1)};

        // check if the last element of the vector of Smileys is selected
        // because it has to be selected for deletion to occur
        if (lastSmileyPtr->GetIsSelected())
        {
            // we had to use a pointer and not a reference because
            // a reference must always be initialized
            PoofParticles *obtainedPoofParticlesPtr{nullptr};

            if (TryGetAvailablePoofParticle(obtainedPoofParticlesPtr))
            {
                // dereference here so we don't have to later
                PoofParticles &poofParticlesEl{*obtainedPoofParticlesPtr};

                // set necessary fields in the obtained PoofParticles object
                poofParticlesEl.SetPosition(lastSmileyPtr->GetPosition());
                poofParticlesEl.SetOuterRadius(lastSmileyPtr->GetRadius());
                poofParticlesEl.SetInnerRadius(lastSmileyPtr->GetRadius() / 3);
                poofParticlesEl.SetLineColor(lastSmileyPtr->GetColor());
            }
            else
            {
                // push another PoofParticles object into the vector
                poofParticles.push_back(PoofParticles{lastSmileyPtr->GetPosition(), lastSmileyPtr->GetRadius() / 2, lastSmileyPtr->GetRadius(), 8});

                // what we are doing here is dereferencing the iterator which points to the end of the last element
                // in the vector, then obtaining the memory address of the object that was dereferenced
                // this is necessary to go from std::vector<PoofParticles>::iterator to PoofParticles*
                // we also need to decrement the vector because, don't forget, it is pointing just right outside the vector
                obtainedPoofParticlesPtr = &*(--poofParticles.end());
            }

            // reset the animation of the PoofParticles
            obtainedPoofParticlesPtr->ResetAnimation();

            // ensure that the PoofParticles show up
            obtainedPoofParticlesPtr->SetShown(true);

            // free up allocated memory used by the smiley
            // then set its pointer to nullptr to prevent dangling pointers
            delete lastSmileyPtr;
            lastSmileyPtr = nullptr;

            // remove the last element of the vector
            smileyPtrs.pop_back();
        }
        else
        {
            // deletion not performed
            // play default system beep sound
            MessageBeep(MB_OK);
        }
    }
    else
    {
        // deletion not performed
        // play default system beep sound
        MessageBeep(MB_OK);
    }
}

void Program::OnCtrlKeyDown(const Vector2f &openGL_mousePosition)
{
    SetCursor(hResizeCursor);

    for (Smiley *&smileyPtr : smileyPtrs)
    {
        smileyPtr->OnCtrlKeyDown(openGL_mousePosition);
    }
}

void Program::OnCtrlKeyUp(const Vector2f &openGL_mousePosition)
{
    SetCursor(hArrowCursor);

    for (Smiley *&smileyPtr : smileyPtrs)
    {
        smileyPtr->OnCtrlKeyUp(openGL_mousePosition);
    }
}

void Program::OnTimerEnd(int deltaTime)
{
    for (PoofParticles &poofParticlesEl : poofParticles)
    {
        if (poofParticlesEl.IsShown())
        {
            poofParticlesEl.Progress(deltaTime);
        }
    }
}

bool Program::TryGetAvailablePoofParticle(PoofParticles *&outPoofParticlesPtr)
{
    for (PoofParticles &poofParticlesEl : poofParticles)
    {
        if (!poofParticlesEl.IsShown())
        {
            outPoofParticlesPtr = &poofParticlesEl;
            return true;
        }
    }

    return false;
}
