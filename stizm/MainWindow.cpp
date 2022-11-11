#include "MainWindow.h"
#include "stizm.h"
#define WIDTH 1280
#define HEIGHT 720
HDC* hDeviceContextGlobal = nullptr;
MainWindow::MainWindow(HINSTANCE _hInstance) : hInstance(_hInstance){
    hDeviceContextGlobal = &hDeviceContext;
}

ATOM MainWindow::Register() {
    mainWindowClass.cbSize = sizeof(WNDCLASSEX);

    mainWindowClass.style = CS_HREDRAW | CS_VREDRAW;
    mainWindowClass.lpfnWndProc = MainWindow::mainWindowProcedure;
    mainWindowClass.cbClsExtra = 0;
    mainWindowClass.cbWndExtra = 0;
    mainWindowClass.hInstance = hInstance;
    mainWindowClass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_STIZM));
    mainWindowClass.hCursor = LoadCursor(nullptr, IDC_ARROW);
    mainWindowClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    mainWindowClass.lpszMenuName = MAKEINTRESOURCEW(IDC_STIZM);
    mainWindowClass.lpszClassName = mainWindowName;
    mainWindowClass.hIconSm = LoadIcon(mainWindowClass.hInstance, MAKEINTRESOURCE(IDI_SMALL));


    return RegisterClassExW(&mainWindowClass);
}



LRESULT MainWindow::mainWindowProcedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message)
    {
    case WM_SIZE: {
        ResizeWindow(WIDTH, HEIGHT);
        return 0;
    }


    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        // Разобрать выбор в меню:
        switch (wmId)
        {
        case IDM_EXIT:
            DestroyWindow(hWnd);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }
    break;
    
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

int MainWindow::Create() {
    Register();
    

    mainWindowHandler = CreateWindowW(
        mainWindowName, 
        L"OpenGL", 
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, 
        WIDTH, HEIGHT, 
        nullptr, 
        nullptr, 
        hInstance, 
        nullptr);

    if (!mainWindowHandler)
    {
        return FALSE;
    }
    CreateContext();
    ShowWindow(mainWindowHandler, SW_SHOW);
    UpdateWindow(mainWindowHandler);

    return TRUE;
}
GLvoid MainWindow::Destroy() {
    if (hRenderContext)                                // Do We Have A Rendering Context?
    {
        if (!wglMakeCurrent(NULL, NULL)) {
            WindowManager::Message("Release Of DC And RC Failed.", Error);
        }
        if (!wglDeleteContext(hRenderContext)) {
            WindowManager::Message("Release Rendering Context Failed.", Error);
        }
        hRenderContext = NULL;
        if (hDeviceContext && !ReleaseDC(mainWindowHandler, hDeviceContext)) {
            WindowManager::Message("Could Not Release hWnd.", Error);
            mainWindowHandler = NULL;
        }
        if (!UnregisterClass(mainWindowName, hInstance))               // Are We Able To Unregister Class
        {
            WindowManager::Message("Could Not Unregister Class.", Error);
            hInstance = NULL;                         // Set hInstance To NULL
        }

    }
}


GLvoid MainWindow::ResizeWindow(GLsizei width, GLsizei height) {
    if (height == 0)                         
    {
        height = 1;                           
    }

    
    glViewport(0, 0, width, height);

}

int MainWindow::CreateContext() {

    GLuint      PixelFormat;

    RECT WindowRect;                            // Grabs Rectangle Upper Left / Lower Right Values
    WindowRect.left = (long)0;                        // Set Left Value To 0
    WindowRect.right = (long)WIDTH;                       // Set Right Value To Requested Width
    WindowRect.top = (long)0;                         // Set Top Value To 0
    WindowRect.bottom = (long)HEIGHT;
    

    static  PIXELFORMATDESCRIPTOR pfd =                  // pfd Tells Windows How We Want Things To Be
    {
        sizeof(PIXELFORMATDESCRIPTOR),                  // Size Of This Pixel Format Descriptor
        1,                              // Version Number
        PFD_DRAW_TO_WINDOW |                        // Format Must Support Window
        PFD_SUPPORT_OPENGL |                        // Format Must Support OpenGL
        PFD_DOUBLEBUFFER,                       // Must Support Double Buffering
        PFD_TYPE_RGBA,                          // Request An RGBA Format
        32,                               // Select Our Color Depth
        0, 0, 0, 0, 0, 0,                       // Color Bits Ignored
        0,                              // No Alpha Buffer
        0,                              // Shift Bit Ignored
        0,                              // No Accumulation Buffer
        0, 0, 0, 0,                         // Accumulation Bits Ignored
        16,                             // 16Bit Z-Buffer (Depth Buffer)
        0,                              // No Stencil Buffer
        0,                              // No Auxiliary Buffer
        PFD_MAIN_PLANE,                         // Main Drawing Layer
        0,                              // Reserved
        0, 0, 0                             // Layer Masks Ignored
    };

    if (!(hDeviceContext = GetDC(mainWindowHandler)))                         // Did We Get A Device Context?
    {
        Destroy();                         // Reset The Display
        WindowManager::Message("Can't Create A GL Device Context.", Error);
        return FALSE;                           // Return FALSE
    }
    if (!(PixelFormat = ChoosePixelFormat(hDeviceContext, &pfd)))             // Did Windows Find A Matching Pixel Format?
    {
        Destroy();                         // Reset The Display
        WindowManager::Message("Can't Find A Suitable PixelFormat.", Error);
        return FALSE;                           // Return FALSE
    }

    if (!SetPixelFormat(hDeviceContext, PixelFormat, &pfd))               // Are We Able To Set The Pixel Format?
    {
        Destroy();                         // Reset The Display
        WindowManager::Message("Can't Set The PixelFormat.", Error);
        return FALSE;                           // Return FALSE
    }
    if (!(hRenderContext = wglCreateContext(hDeviceContext)))                   // Are We Able To Get A Rendering Context?
    {
        Destroy();                         // Reset The Display
        WindowManager::Message("Can't Create A GL Rendering Context.", Error);
        return FALSE;                           // Return FALSE
    }
    if (!wglMakeCurrent(hDeviceContext, hRenderContext))                        // Try To Activate The Rendering Context
    {
        Destroy();                         // Reset The Display
        WindowManager::Message("Can't Activate The GL Rendering Context.", Error);
        return FALSE;                           // Return FALSE
    }

    ResizeWindow(WIDTH, HEIGHT);

    //if ()                              // Initialize Our Newly Created GL Window
    //{
    //    Destroy();                         // Reset The Display
    //    WindowManager::Message("Initialization Failed.", Error);
    //    return FALSE;                           // Return FALSE
    //}

    return TRUE;
}