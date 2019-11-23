/**
 * IGRA Assignment 1: Smiley Editor
 * Completed by Brandon Gui (1828865) from DIT/FT/2B05.
 */

// OpenGLApplication.cpp : Defines the entry point for the application.
//

#include "OpenGLApplication.h"

#include "BrandonUtils.h"       // for converting from window coordinates to OpenGL coordinates
#include "Program.h"            // custom class to abstract all these
#include "Vector2f.h"           // for mouse position

#include "framework.h"          // include file for standard system include files or project specific include files
                                // which also includes the necessary files for drawing OpenGL shapes
#include "Windowsx.h"           // for GET_X_L_PARAM and GET_Y_LPARAM

#include <gl/GL.h>              // OpenGL 32-bit library
#include <gl/GLU.h>             // GLU 32-bit library

#define MAX_LOADSTRING 100

// defines for extra width and height due to window toolbar and border
constexpr int extraWidth{16};
constexpr int extraHeight{60};

/// <summary>
/// The length of the timer in milliseconds before it loops over.
/// The value is determined by dividing 100 milliseconds by 60 frames to
/// get the duration between timer calls.
/// </summary>
constexpr int timerDuration{16};

// Global Variables:
Vector2f windowSize{400.f, 400.f};
Vector2f mousePosition{0.f, 0.f};
GLuint PixelFormat;                     // Type is an OpenGL pre-defined unsigned int. These types ensure cross-platform compatibility.
HDC hDC = NULL;                         // A handle to the device context
HWND hWnd = NULL;                       // A handle to the window
HGLRC hRC = NULL;                       // A handle to an OpenGL Rendering Context
HINSTANCE hInst;                        // current instance
WCHAR szTitle[MAX_LOADSTRING];          // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];    // the main window class name

Program *ptrProgram { new Program{} };

// Pixel Format Descriptor
static PIXELFORMATDESCRIPTOR pfd
{
    sizeof(PIXELFORMATDESCRIPTOR),
    1,                      // version number
    PFD_DRAW_TO_WINDOW |    // format must support window
    PFD_SUPPORT_OPENGL |    // format must support OpenGL
    PFD_DOUBLEBUFFER,       // must support double buffering
    PFD_TYPE_RGBA,          // request an RGBA format
    16,                     // select our colour depth, which will be 16
    0, 0, 0, 0, 0, 0,       // colour bits ignored
    0,                      // no alpha buffer
    0,                      // shift bit ignored
    0,                      // no accumulation buffer
    0, 0, 0, 0,             // accumulation bits ignored
    32,                     // 32-bit Z-Buffer (depth buffer)
    0,                      // no stencil buffer
    0,                      // no auxiliary buffer
    PFD_MAIN_PLANE,         // main drawing layer
    0,                      // reserved
    0, 0, 0                 // layer masks ignored
};

// Forward declarations created by this developer:
    int InitOpenGL();
    void ReSizeGLScene(GLsizei width, GLsizei height);
    void DrawGLScene();

    /// <summary>
    /// A callback function that gets called by the timer at a specified interval.
    /// The calling convention must match those of TIMERPROC.
    /// See https://docs.microsoft.com/en-us/windows/win32/winmsg/using-timers for more details.
    /// </summary>
    void TimerProc(HWND Arg1, UINT Arg2, UINT_PTR Arg3, DWORD Arg4);

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_OPENGLAPPLICATION, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_OPENGLAPPLICATION));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);

            DrawGLScene();
            SwapBuffers(hDC);
        }
    }

    return (int) msg.wParam;
}

void TimerProc(HWND Arg1, UINT Arg2, UINT_PTR Arg3, DWORD Arg4)
{
    ptrProgram->OnTimerEnd(timerDuration);
}

//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_OPENGLAPPLICATION));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_OPENGLAPPLICATION);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   // the third parameter of the CreateWindowW method accepts a bitmask where you can specify which styles to use
   // you can see all of the available window styles here: https://docs.microsoft.com/en-us/windows/win32/winmsg/window-styles?redirectedfrom=MSDN
   // here, we create a window with the following style:
   // - WS_VISIBLE:    The window is initially visible (so that we can see it at the start)
   // - WS_CAPTION:    The window has a title bar showing its name. This bit also includes WS_BORDER so we don't need to state it again.
   // - WS_SYSMENU:    The window has a window menu on its title bar. This allows users to click on the "X" button on the right to close it.
   // We didn't include a minimize (WS_MINIMIZEBOX) and maximize button (WS_MAXIMIZEBOX) because we don't require it
   // and we also don't want to resize the window.
   hWnd = CreateWindowW(szWindowClass, szTitle, WS_VISIBLE | WS_CAPTION | WS_SYSMENU, 0, 0, windowSize.x + extraWidth, windowSize.y + extraHeight, nullptr, nullptr, hInstance, nullptr);

   // set the window title name to my name, as per the requirements
   // L"any string here" is a wchar_t literal
   SetWindowTextW(hWnd, L"IGRA Assignment 1: Brandon Gui");

   InitOpenGL();

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   ReSizeGLScene(windowSize.x, windowSize.y);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND      - process the application menu
//  WM_PAINT        - Paint the main window
//  WM_DESTROY      - post a quit message and return
//  WM_SIZE         - called when the window is resized
//  WM_MOUSEMOVE    - called when the cursor is moved inside the window
//  WM_LBUTTONDOWN  - called when the left mouse button is pressed while the cursor is inside the window
//  WM_RBUTTONDOWN  - called when the right mouse button is pressed while the cursor is inside the window
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
        case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
                case IDM_ABOUT:
                    DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                    break;
                case IDM_EXIT:
                    DestroyWindow(hWnd);
                    break;
                default:
                    return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
        case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Add any drawing code that uses hdc here...
            EndPaint(hWnd, &ps);
        }
        break;
        case WM_SIZE:
        {
            ReSizeGLScene(LOWORD(lParam), LOWORD(lParam));
            break;
        }
        case WM_MOUSEMOVE:
        {
            mousePosition.x = GET_X_LPARAM(lParam);
            mousePosition.y = GET_Y_LPARAM(lParam);

            // TODO: Optimize so that you don't keep returning a Vector2f (does constantly returning something cause performance problems?)
            // convert the current mouse coordinates to OpenGL coordinates
            ptrProgram->OnMouseMove(BrandonUtils::winCoordsToOpenGL(mousePosition, windowSize), wParam);
            break;
        }
        case WM_LBUTTONDOWN:
        {
            mousePosition.x = GET_X_LPARAM(lParam);
            mousePosition.y = GET_Y_LPARAM(lParam);

            // convert current mouse coordinates to OpenGL coordinates
            ptrProgram->OnLMouseButtonDown(BrandonUtils::winCoordsToOpenGL(mousePosition, windowSize));
            
            break;
        }
        case WM_RBUTTONDOWN:
        {
            mousePosition.x = GET_X_LPARAM(lParam);
            mousePosition.y = GET_Y_LPARAM(lParam);

            // convert current mouse coordinates to OpenGL coordinates
            ptrProgram->OnRMouseButtonDown(BrandonUtils::winCoordsToOpenGL(mousePosition, windowSize));
            break;
        }
        case WM_KEYDOWN:
        {
            switch (wParam)
            {
                // ctrl key
                case VK_CONTROL:
                    ptrProgram->OnCtrlKeyDown(BrandonUtils::winCoordsToOpenGL(mousePosition, windowSize));
                    break;

                // delete key
                case VK_DELETE:
                    ptrProgram->OnDelKeyDown();
                    break;
            }

            break;
        }
        case WM_KEYUP:
        {
            switch (wParam)
            {
                // ctrl key
                case VK_CONTROL:
                    ptrProgram->OnCtrlKeyUp(BrandonUtils::winCoordsToOpenGL(mousePosition, windowSize));
                    break;
            }

            break;
        }
        case WM_SETCURSOR:  // this message must be processed or else the system redraws the cursor and it will flicker
        {

            break;
        }
        case WM_DESTROY:

            // save all smileys to a text file
            ptrProgram->SaveSmileysToFile();

            // deallocate memory occupied by the Program instance
            // then set its pointer to nullptr to prevent dangling pointers
            delete ptrProgram;
            ptrProgram = nullptr;

            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

int InitOpenGL()
{
    // get device context
    if (!(hDC = GetDC(hWnd)))
    {
        MessageBox(
            NULL,
            L"Can't create a GL device context!",
            L"ERROR",
            MB_OK | MB_ICONEXCLAMATION
        );
        return 0;
    }

    // check if Windows can find a matching pixel format
    if (!(PixelFormat = ChoosePixelFormat(hDC, &pfd)))
    {
        MessageBox(
            NULL,
            L"Can't find a suitable pixel format!",
            L"ERROR",
            MB_OK | MB_ICONEXCLAMATION
        );
        return 0;
    }

    // try to set the pixel format
    if (!SetPixelFormat(hDC, PixelFormat, &pfd))
    {
        MessageBox(
            NULL,
            L"Can't create a GL rendering context!",
            L"ERROR",
            MB_OK | MB_ICONEXCLAMATION
        );
        return 0;
    }

    // get a rendering context
    if (!(hRC = wglCreateContext(hDC)))
    {
        MessageBox(
            NULL,
            L"Can't set the pixel format!",
            L"ERROR",
            MB_OK | MB_ICONEXCLAMATION
        );
        return 0;
    }

    // activate rendering context
    if (!wglMakeCurrent(hDC, hRC))
    {
        MessageBox(
            NULL,
            L"Can't activate the GL rendering context!",
            L"ERROR",
            MB_OK | MB_ICONEXCLAMATION
        );
        return 0;
    }

    // for solving the depth-buffer issue
    glClearDepth(1.0f);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    // sets a timer that calls the given callback function at a certain interval
    SetTimer(hWnd, NULL, timerDuration, (TIMERPROC) TimerProc);

    return 1;
}

void ReSizeGLScene(GLsizei width, GLsizei height)
{
    // prevent a division by zero error by setting the height to 1
    if (height == 0)
        height = 1;

    // reset the current viewport
    glViewport(0, 0, width, height);

    // select the projection matrix
    glMatrixMode(GL_PROJECTION);

    // reset the projection matrix
    glLoadIdentity();

    // calculate the aspect ratio of the window
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
}

void DrawGLScene()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(1, 1, 1, 1);

    // check to see if the pointer to the Program instance is NOT a null pointer
    // then allow execution
    // this helps to prevent undefined behaviour
    if (ptrProgram != nullptr)
    {
        ptrProgram->Draw();
    }
}