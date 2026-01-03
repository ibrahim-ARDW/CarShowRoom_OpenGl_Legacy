
#include <windows.h>    // Header File For Windows
#include <gl.h>      // Header File For The OpenGL32 Library
#include <glu.h>      // Header File For The GLu32 Library
#include <glaux.h>    // Header File For The Glaux Library
#include <cmath>
#include "Camera.h"
#include "CollisionManager.h"
#include "LoadPngTexture.h"
#include "DrawAllShapes.h"
#include "OBJLoader.h"
#include "Mesh.h"
#include "Car.h"




HDC      hDC = NULL;    // Private GDI Device Context
HGLRC    hRC = NULL;    // Permanent Rendering Cntext
HWND    hWnd = NULL;    // Holds Our Window Handle
HINSTANCE  hInstance;    // Holds The Instance Of The Application

bool  keys[256];      // Array Used For The Keyboard Routine
bool  active = TRUE;    // Window Active Flag Set To TRUE By Default
bool  fullscreen = FALSE;  // Fullscreen Flag Set To Fullscreen Mode By Default

LRESULT  CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);  // Declaration For WndProc

GLvoid ReSizeGLScene(GLsizei width, GLsizei height)    // Resize And Initialize The GL Window
{
    if (height == 0)                    // Prevent A Divide By Zero By
    {
        height = 1;                    // Making Height Equal One
    }

    glViewport(0, 0, width, height);            // Reset The Current Viewport

    glMatrixMode(GL_PROJECTION);            // Select The Projection Matrix
    glLoadIdentity();                  // Reset The Projection Matrix

    // Calculate The Aspect Ratio Of The Window
    gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f);

    glMatrixMode(GL_MODELVIEW);              // Select The Modelview Matrix
    glLoadIdentity();                  // Reset The Modelview Matrix
}
Camera camera;
float speed = 0.015f;
//Car MyCar;
GLuint grass;

//std::vector<Mesh> carMeshes;

int InitGL(GLvoid)                    // All Setup For OpenGL Goes Here
{
    glShadeModel(GL_SMOOTH);              // Enable Smooth Shading
    glClearColor(0.03f, 0.16f, 0.33f, 1.0f);        // Black Background
    glClearDepth(1.0f);                  // Depth Buffer Setup
    ShowCursor(FALSE);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_DEPTH_TEST);              // Enables Depth Testing
    glDepthFunc(GL_LEQUAL);                // The Type Of Depth Testing To Do
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // Really Nice Perspective Calculations
    //glEnable(GL_BLEND); // ÊÝÚíá ÎÇÕíÉ ÇáÏãÌ (ááÔÝÇÝíÉ)
   // glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    GLfloat ambientLight[] = { 0.2f, 0.2f, 0.2f, 1.0f }; // ÖæÁ ãÍíØí ÎÇÝÊ ááÙáÇá
    GLfloat diffuseLight[] = { 0.8f, 0.8f, 0.8f, 1.0f }; // ÖæÁ ÃÓÇÓí ãÊæÇÒä
    GLfloat specularLight[] = { 0.5f, 0.5f, 0.5f, 1.0f }; // áãÚÇä ãÚÊÏá
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING); // ÊÝÚíá ÇáÅÖÇÁÉ ÚÇáãíÇð
    // ÓØÑ ÓÍÑí: íãäÚ ÇáÖæÁ ãä ÇáÇäÝÌÇÑ ÚäÏ Úãá Scale ááãæÏíá
    glEnable(GL_NORMALIZE);
    // ÊÝÚíá ÊÝÇÚá ÇáÃáæÇä ãÚ ÇáÅÖÇÁÉ
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    Car::load("carOBJ/car.obj");
    //if (!OBJLoader::loadOBJ("carOBJ/car.obj", carMeshes)) {
    //    MessageBox(NULL, L"Failed to load car model!", L"Error", MB_OK);
    //    return FALSE;
    //}
    //// ÊÍæíá ÇáÈíÇäÇÊ Åáì Display Lists áÒíÇÏÉ ÓÑÚÉ ÇáÑÓã (FPS)
    //OBJLoader::createDisplayLists(carMeshes);
    grass = LoadTexturePng::loadTexture("grass.png");

    return TRUE;                    // Initialization Went OK
}


int DrawGLScene(GLvoid)                  // Here's Where We Do All The Drawing
{
    CollisionManager::clear();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glEnable(GL_TEXTURE_2D);
    // ßæÏ ÇáÞÝÒ (ßãÇ åæ ÈÏæä ÊÛííÑ)
    if (camera.jumping)
    {
        camera.jumpTime += 0.0005f;
        float jumpHeight = 4.0f;
        camera.y = camera.jumpStartY + sinf(camera.jumpTime * 3.14159f) * jumpHeight;
        if (camera.jumpTime >= 1.0f)
        {
            camera.jumping = false;
            camera.y = camera.height;
        }
    }

   // camera.updateView();

    

    if (Car::isDriven) {
        Car::updateDriving(keys, camera);
    }

    camera.updateView(); // ? ÏÇíãðÇ ÏÇíãðÇ ÏÇíãðÇ

    GLfloat lightPos[] = { 5.0f, 10.0f, 5.0f, 1.0f };
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

    // 1. ÑÓã ÇáÃÑÖíÉ (äÊÃßÏ ãä ÅÚØÇÆåÇ áæäÇð ÃÈíÖÇð áÊÙåÑ ÇáÊßÓÊÔÑ ØÈíÚíÉ)
    glColor3f(1.0f, 1.0f, 1.0f);
    DrawShapes::drawFloor(grass);
    Car::draw();

   // SwapBuffers(wglGetCurrentDC());

    return TRUE;
}

GLvoid KillGLWindow(GLvoid)                // Properly Kill The Window
{
 
    if (fullscreen)                    // Are We In Fullscreen Mode?
    {
        ChangeDisplaySettings(NULL, 0);          // If So Switch Back To The Desktop
        ShowCursor(TRUE);                // Show Mouse Pointer
    }

    if (hRC)                      // Do We Have A Rendering Context?
    {
        if (!wglMakeCurrent(NULL, NULL))          // Are We Able To Release The DC And RC Contexts?
        {
            // Replace all instances of MessageBox with the following code to fix the errors  
            MessageBox(NULL, L"Release Of DC And RC Failed.", L"SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
        }


        if (!wglDeleteContext(hRC))            // Are We Able To Delete The RC?
        {
            MessageBox(NULL, L"Release Rendering Context Failed.", L"SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
        }
        hRC = NULL;                    // Set RC To NULL
    }

    if (hDC && !ReleaseDC(hWnd, hDC))          // Are We Able To Release The DC
    {
        MessageBox(NULL, L"Release Device Context Failed.", L"SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
        hDC = NULL;                    // Set DC To NULL
    }

    if (hWnd && !DestroyWindow(hWnd))          // Are We Able To Destroy The Window?
    {
        MessageBox(NULL, L"Could Not Release hWnd.", L"SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
        hWnd = NULL;                    // Set hWnd To NULL
    }

    if (!UnregisterClass(L"OpenGL", hInstance))      // Are We Able To Unregister Class
    {
        MessageBox(NULL, L"Could Not Unregister Class.", L"SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
        hInstance = NULL;                  // Set hInstance To NULL
    }
}

/*  This Code Creates Our OpenGL Window.  Parameters Are:          *
*  title      - Title To Appear At The Top Of The Window        *
*  width      - Width Of The GL Window Or Fullscreen Mode        *
*  height      - Height Of The GL Window Or Fullscreen Mode      *
*  bits      - Number Of Bits To Use For Color (8/16/24/32)      *
*  fullscreenflag  - Use Fullscreen Mode (TRUE) Or Windowed Mode (FALSE)  */

BOOL CreateGLWindow(LPCWSTR  title, int width, int height, int bits, bool fullscreenflag)
{
    GLuint    PixelFormat;      // Holds The Results After Searching For A Match
    WNDCLASS  wc;            // Windows Class Structure
    DWORD    dwExStyle;        // Window Extended Style
    DWORD    dwStyle;        // Window Style
    RECT    WindowRect;        // Grabs Rectangle Upper Left / Lower Right Values
    WindowRect.left = (long)0;      // Set Left Value To 0
    WindowRect.right = (long)width;    // Set Right Value To Requested Width
    WindowRect.top = (long)0;        // Set Top Value To 0
    WindowRect.bottom = (long)height;    // Set Bottom Value To Requested Height

    fullscreen = fullscreenflag;      // Set The Global Fullscreen Flag

    hInstance = GetModuleHandle(NULL);        // Grab An Instance For Our Window
    wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;  // Redraw On Size, And Own DC For Window.
    wc.lpfnWndProc = (WNDPROC)WndProc;          // WndProc Handles Messages
    wc.cbClsExtra = 0;                  // No Extra Window Data
    wc.cbWndExtra = 0;                  // No Extra Window Data
    wc.hInstance = hInstance;              // Set The Instance
    wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);      // Load The Default Icon
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);      // Load The Arrow Pointer
    wc.hbrBackground = NULL;                  // No Background Required For GL
    wc.lpszMenuName = NULL;                  // We Don't Want A Menu
    wc.lpszClassName = L"OpenGL";                // Set The Class Name

    if (!RegisterClass(&wc))                  // Attempt To Register The Window Class
    {
        MessageBox(NULL, L"Failed To Register The Window Class.", L"ERROR", MB_OK | MB_ICONEXCLAMATION);
        return FALSE;                      // Return FALSE
    }

    if (fullscreen)                        // Attempt Fullscreen Mode?
    {
        DEVMODE dmScreenSettings;                // Device Mode
        memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));  // Makes Sure Memory's Cleared
        dmScreenSettings.dmSize = sizeof(dmScreenSettings);    // Size Of The Devmode Structure
        dmScreenSettings.dmPelsWidth = width;        // Selected Screen Width
        dmScreenSettings.dmPelsHeight = height;        // Selected Screen Height
        dmScreenSettings.dmBitsPerPel = bits;          // Selected Bits Per Pixel
        dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;


        // Try To Set Selected Mode And Get Results.  NOTE: CDS_FULLSCREEN Gets Rid Of Start Bar.
        if (ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
        {
            // If The Mode Fails, Offer Two Options.  Quit Or Use Windowed Mode.
            if (MessageBox(NULL, L"The Requested Fullscreen Mode Is Not Supported By\nYour Video Card. Use Windowed Mode Instead?", L"GL template", MB_YESNO | MB_ICONEXCLAMATION) == IDYES)
            {
                fullscreen = FALSE;    // Windowed Mode Selected.  Fullscreen = FALSE
            }
            else
            {
                // Pop Up A Message Box Letting User Know The Program Is Closing.
                MessageBox(NULL, L"Program Will Now Close.", L"ERROR", MB_OK | MB_ICONSTOP);
                return FALSE;                  // Return FALSE
            }
        }
    }

    if (fullscreen)                        // Are We Still In Fullscreen Mode?
    {
        dwExStyle = WS_EX_APPWINDOW;                // Window Extended Style
        dwStyle = WS_POPUP;                    // Windows Style
        ShowCursor(FALSE);                    // Hide Mouse Pointer
    }
    else
    {
        dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;      // Window Extended Style
        dwStyle = WS_OVERLAPPEDWINDOW;              // Windows Style
    }

    AdjustWindowRectEx(&WindowRect, dwStyle, FALSE, dwExStyle);    // Adjust Window To True Requested Size

    // Create The Window

    if (!(hWnd = CreateWindowEx(dwExStyle,              // Extended Style For The Window
        L"OpenGL",              // Class Name
        title,                // Window Title
        dwStyle |              // Defined Window Style
        WS_CLIPSIBLINGS |          // Required Window Style
        WS_CLIPCHILDREN,          // Required Window Style
        0, 0,                // Window Position
        WindowRect.right - WindowRect.left,  // Calculate Window Width
        WindowRect.bottom - WindowRect.top,  // Calculate Window Height
        NULL,                // No Parent Window
        NULL,                // No Menu
        hInstance,              // Instance
        NULL)))                // Dont Pass Anything To WM_CREATE
    {
        KillGLWindow();                // Reset The Display
        MessageBox(NULL, L"Window Creation Error.", L"ERROR", MB_OK | MB_ICONEXCLAMATION);
        return FALSE;                // Return FALSE
    }

    static  PIXELFORMATDESCRIPTOR pfd =        // pfd Tells Windows How We Want Things To Be
    {
      sizeof(PIXELFORMATDESCRIPTOR),        // Size Of This Pixel Format Descriptor
      1,                      // Version Number
      PFD_DRAW_TO_WINDOW |            // Format Must Support Window
      PFD_SUPPORT_OPENGL |            // Format Must Support OpenGL
      PFD_DOUBLEBUFFER,              // Must Support Double Buffering
      PFD_TYPE_RGBA,                // Request An RGBA Format
      bits,                    // Select Our Color Depth
      0, 0, 0, 0, 0, 0,              // Color Bits Ignored
      0,                      // No Alpha Buffer
      0,                      // Shift Bit Ignored
      0,                      // No Accumulation Buffer
      0, 0, 0, 0,                  // Accumulation Bits Ignored
      16,                      // 16Bit Z-Buffer (Depth Buffer)  
      0,                      // No Stencil Buffer
      0,                      // No Auxiliary Buffer
      PFD_MAIN_PLANE,                // Main Drawing Layer
      0,                      // Reserved
      0, 0, 0                    // Layer Masks Ignored
    };

    if (!(hDC = GetDC(hWnd)))              // Did We Get A Device Context?
    {
        KillGLWindow();                // Reset The Display
        MessageBox(NULL, L"Can't Create A GL Device Context.", L"ERROR", MB_OK | MB_ICONEXCLAMATION);
        return FALSE;                // Return FALSE
    }

    if (!(PixelFormat = ChoosePixelFormat(hDC, &pfd)))  // Did Windows Find A Matching Pixel Format?
    {
        KillGLWindow();                // Reset The Display
        MessageBox(NULL, L"Can't Find A Suitable PixelFormat.", L"ERROR", MB_OK | MB_ICONEXCLAMATION);
        return FALSE;                // Return FALSE
    }


    if (!SetPixelFormat(hDC, PixelFormat, &pfd))    // Are We Able To Set The Pixel Format?
    {
        KillGLWindow();                // Reset The Display
        MessageBox(NULL, L"Can't Set The PixelFormat.", L"ERROR", MB_OK | MB_ICONEXCLAMATION);
        return FALSE;                // Return FALSE
    }

    if (!(hRC = wglCreateContext(hDC)))        // Are We Able To Get A Rendering Context?
    {
        KillGLWindow();                // Reset The Display
        MessageBox(NULL, L"Can't Create A GL Rendering Context.", L"ERROR", MB_OK | MB_ICONEXCLAMATION);
        return FALSE;                // Return FALSE
    }

    if (!wglMakeCurrent(hDC, hRC))          // Try To Activate The Rendering Context
    {
        KillGLWindow();                // Reset The Display
        MessageBox(NULL, L"Can't Activate The GL Rendering Context.", L"ERROR", MB_OK | MB_ICONEXCLAMATION);
        return FALSE;                // Return FALSE
    }

    ShowWindow(hWnd, SW_SHOW);            // Show The Window
    SetForegroundWindow(hWnd);            // Slightly Higher Priority
    SetFocus(hWnd);                  // Sets Keyboard Focus To The Window
    ReSizeGLScene(width, height);          // Set Up Our Perspective GL Screen

    if (!InitGL())                  // Initialize Our Newly Created GL Window
    {
        KillGLWindow();                // Reset The Display
        MessageBox(NULL, L"Initialization Failed.", L"ERROR", MB_OK | MB_ICONEXCLAMATION);
        return FALSE;                // Return FALSE
    }

    return TRUE;                  // Success
}

LRESULT CALLBACK WndProc(HWND  hWnd,      // Handle For This Window
    UINT  uMsg,      // Message For This Window
    WPARAM  wParam,      // Additional Message Information
    LPARAM  lParam)      // Additional Message Information
{
    switch (uMsg)                  // Check For Windows Messages
    {
    case WM_KEYDOWN:
    {
        keys[wParam] = TRUE;

        if (wParam == 'G')  // ÅÐÇ ÖÛØ ÇáãÓÊÎÏã Úáì E
        {
            static bool cursorVisible = false;
            cursorVisible = !cursorVisible; // ÇáÊÈÏíá Èíä ÇáÅÙåÇÑ æÇáÅÎÝÇÁ

            ShowCursor(cursorVisible);
        }

        return 0;
    }
    case WM_MOUSEMOVE:
    {
        int mouseX = LOWORD(lParam);
        int mouseY = HIWORD(lParam);

        static int lastX = mouseX;
        static int lastY = mouseY;

        int deltaX = mouseX - lastX;
        int deltaY = mouseY - lastY;

        lastX = mouseX;
        lastY = mouseY;

        camera.yaw += deltaX * 0.2f;    // ÍÓÇÓíÉ
        camera.pitch -= deltaY * 0.2f;

        if (camera.pitch > 89.0f) camera.pitch = 89.0f;
        if (camera.pitch < -89.0f) camera.pitch = -89.0f;

        return 0;
    }
    case WM_ACTIVATE:              // Watch For Window Activate Message
    {
        if (!HIWORD(wParam))          // Check Minimization State
        {
            active = TRUE;            // Program Is Active
        }
        else
        {
            active = FALSE;            // Program Is No Longer Active
        }

        return 0;                // Return To The Message Loop
    }

    case WM_SYSCOMMAND:              // Intercept System Commands
    {
        switch (wParam)              // Check System Calls
        {
        case SC_SCREENSAVE:          // Screensaver Trying To Start?
        case SC_MONITORPOWER:        // Monitor Trying To Enter Powersave?
            return 0;              // Prevent From Happening
        }
        break;                  // Exit
    }

    case WM_CLOSE:                // Did We Receive A Close Message?
    {
        PostQuitMessage(0);            // Send A Quit Message
        return 0;                // Jump Back
    }

    //case WM_KEYDOWN:              // Is A Key Being Held Down?
    //{
    //    keys[wParam] = TRUE;          // If So, Mark It As TRUE
    //    return 0;                // Jump Back
    //}

    case WM_KEYUP:                // Has A Key Been Released?
    {
        keys[wParam] = FALSE;          // If So, Mark It As FALSE
        return 0;                // Jump Back
    }

    case WM_SIZE:                // Resize The OpenGL Window
    {
        ReSizeGLScene(LOWORD(lParam), HIWORD(lParam));  // LoWord=Width, HiWord=Height
        return 0;                // Jump Back
    }
    }

    // Pass All Unhandled Messages To DefWindowProc
    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE  hInstance,      // Instance
    HINSTANCE  hPrevInstance,    // Previous Instance
    LPSTR    lpCmdLine,      // Command Line Parameters
    int      nCmdShow)      // Window Show State
{
    MSG    msg;                  // Windows Message Structure
    BOOL  done = FALSE;                // Bool Variable To Exit Loop

    // Ask The User Which Screen Mode They Prefer
    //if (MessageBox(NULL,"Would You Like To Run In Fullscreen Mode?", "Start FullScreen?",MB_YESNO|MB_ICONQUESTION)==IDNO)
    {
        fullscreen = FALSE;              // Windowed Mode
    }

    // Create Our OpenGL Window
    if (!CreateGLWindow(L"OpenGL template", 1920, 1080, 32, fullscreen))
    {
        return 0;                  // Quit If Window Was Not Created
    }


    while (!done)                  // Loop That Runs While done=FALSE
    {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))  // Is There A Message Waiting?
        {
            if (msg.message == WM_QUIT)        // Have We Received A Quit Message?
            {
                done = TRUE;              // If So done=TRUE
            }
            else                  // If Not, Deal With Window Messages
            {
                TranslateMessage(&msg);        // Translate The Message
                DispatchMessage(&msg);        // Dispatch The Message
            }
        }
        else                    // If There Are No Messages
        {
            // Draw The Scene.  Watch For ESC Key And Quit Messages From DrawGLScene()
            if (active)                // Program Active?
            {
                if (keys[VK_ESCAPE])        // Was ESC Pressed?
                {
                    done = TRUE;            // ESC Signalled A Quit
                }
                else                // Not Time To Quit, Update Screen
                {
                    DrawGLScene();          // Draw The Scene
                    SwapBuffers(hDC);        // Swap Buffers (Double Buffering)
                }
            }

            if (keys['A'])
            {
                camera.moveLeft(speed);
            }

            if (keys['S'])
            {
                camera.moveBackward(speed);
            }

            if (keys['W'])
            {
                camera.moveForward(speed);
            }

            if (keys['D'])
            {
                camera.moveRight(speed);
            }
            if (keys[VK_SPACE])
            {
                camera.jump();

            }
            if (keys[VK_SHIFT])
            {
                camera.shiftDown(0.5f);

            }
            else camera.y = camera.height;
            if (keys['E'])
            {
                //float dist = sqrt(pow(Car::x - camera.x, 2) + pow(Car::z - camera.z, 2));
                //if (dist < 3.0f || Car::isDriven) {
                //    Car::mount(camera); // ÓíäÞá ÇáßÇãíÑÇ ÝæÑÇð
                //}

                Car::mount(camera);
            }

         /*   if (keys['R'])
            {
                angle6 += x;
            }*/

            if (keys[VK_F1])            // Is F1 Being Pressed?
            {
                keys[VK_F1] = FALSE;          // If So Make Key FALSE
                KillGLWindow();            // Kill Our Current Window
                fullscreen = !fullscreen;        // Toggle Fullscreen / Windowed Mode
                // Recreate Our OpenGL Window
                if (!CreateGLWindow(L"OpenGL template", 640, 480, 16, fullscreen))
                {
                    return 0;            // Quit If Window Was Not Created
                }
            }
        }
    }

    // Shutdown
    KillGLWindow();                  // Kill The Window
    return (msg.wParam);              // Exit The Program
}