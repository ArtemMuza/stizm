#include "MainWindow.h"
#include "stizm.h"
#define WIDTH 1280
#define HEIGHT 720

#define BTN_GEN 500

#define EDT_FRST 601
#define EDT_SCND 602

#define CHCK_FRST 701

#define CMND_WND 10000

#define Radio1 10001
#define Radio2 10002
#define Radio3 10003

HWND hEditWidth = NULL;
HWND hEditHeight = NULL;

HWND hwndButton = NULL;

HWND hwndRadioB1 = NULL;
HWND hwndRadioB2 = NULL;
HWND hwndRadioB3 = NULL;

int styleUsed = 0;

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
    int buffW, buffH;
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
        case BTN_GEN:
        {
            wchar_t width[3], height[3];

            GetWindowTextW(hEditWidth, width, 3);
            GetWindowTextW(hEditHeight, height, 3);


            if (!((char)width[1] >= '0' && (char)width[1] <= '9')) {
                if (width[0] > '9' || width[0] < '0')
                    width[0] = 0;

                buffW = (char)width[0] - '0';
            }
            else
                buffW = ((char)width[0] - '0') * 10 + (char)width[1] - '0';

            if (!((char)height[1] >= '0' && (char)height[1] <= '9')) {
                if (height[0] > '9' || height[0] < '0')
                    height[0] = 0;

                buffH = (char)height[0] - '0';
            }
            else
                buffH = ((char)height[0] - '0') * 10 + (char)height[1] - '0';

            

            RenderManager::getInstance().ChangeValues(buffW, buffH, styleUsed);

            break;
        }
        case Radio1:
            styleUsed = 0;
            break;
        case Radio2:
            styleUsed = 1;
            break;
        case Radio3:
            styleUsed = 2;
            break;

        case IDM_EXIT: 
        {
            DestroyWindow(hWnd);
            break;
        }
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
 

    if (NULL == (mainMenuHandler = CreateWindowW(
        mainWindowName,
        L"OpenGL",
        WS_BORDER,
        CW_USEDEFAULT, 0,
        WIDTH*1.1, HEIGHT*1.1,
        mainWindowHandler,
        nullptr,
        hMenuInstance,
        nullptr)))
        return FALSE;

    if (NULL == (mainWindowHandler = CreateWindowW(
        mainWindowName, 
        L"OpenGL", 
        WS_CHILD,
        CW_USEDEFAULT, 0, 
        WIDTH, HEIGHT*1.1, 
        mainMenuHandler, 
        nullptr, 
        hInstance, 
        nullptr)))
        return FALSE;

    

    

    if (NULL == (hwndButton = CreateWindow(
        L"BUTTON",  // Predefined class; Unicode assumed 
        L"GENERATE",      // Button text 
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
        (WIDTH), 130, (WIDTH*0.09), 100,
        mainMenuHandler,     // Parent window
        (HMENU)BTN_GEN,       // No menu.
        (HINSTANCE)GetWindowLongPtr(mainWindowHandler, GWLP_HINSTANCE),
        NULL)))// Pointer not needed.
        return FALSE;

    if (NULL == (hEditWidth = CreateWindow(
        L"EDIT",
        L"1",
        WS_BORDER | WS_CHILD | WS_VISIBLE | WS_VSCROLL | ES_LEFT |
        ES_MULTILINE | ES_AUTOVSCROLL,
        WIDTH+10, 20, 40, 20,
        mainMenuHandler,
        (HMENU)EDT_FRST,
        (HINSTANCE)GetWindowLongPtr(mainWindowHandler, GWLP_HINSTANCE),
        NULL)))
        return FALSE;

    if (NULL == (hEditHeight = CreateWindow(
        L"EDIT",
        L"1",
        WS_BORDER | WS_CHILD | WS_VISIBLE | WS_VSCROLL | ES_LEFT |
        ES_MULTILINE | ES_AUTOVSCROLL,
        WIDTH+70, 20, 40, 20,
        mainMenuHandler,
        (HMENU)EDT_SCND,
        (HINSTANCE)GetWindowLongPtr(mainWindowHandler, GWLP_HINSTANCE),
        NULL)))
        return FALSE;

    if (NULL == (hwndRadioB1 = CreateWindow(
        L"button", 
        L"Line mode",
        WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
        WIDTH+10, 50, 95, 30, 
        mainMenuHandler, 
        (HMENU)Radio1, (HINSTANCE)GetWindowLongPtr(mainWindowHandler, GWLP_HINSTANCE), 
        NULL)))
        return FALSE;

    if (NULL == (hwndRadioB1 = CreateWindow(
        L"button", 
        L"Fill mode",
        WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
        WIDTH+10, 75, 95, 30,
        mainMenuHandler,
        (HMENU)Radio2, (HINSTANCE)GetWindowLongPtr(mainWindowHandler, GWLP_HINSTANCE),
        NULL)))
        return FALSE;

    if (NULL == (hwndRadioB1 = CreateWindow(
        L"button", 
        L"Point mode",
        WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
        WIDTH+10, 100, 95, 30,
        mainMenuHandler,
        (HMENU)Radio3, (HINSTANCE)GetWindowLongPtr(mainWindowHandler, GWLP_HINSTANCE),
        NULL)))
        return FALSE;


        


    if (!mainWindowHandler )
    {
        return FALSE;
    }
    CreateContext();
    ShowWindow(mainWindowHandler, SW_SHOW);
    ShowWindow(mainMenuHandler, SW_SHOW);

    UpdateWindow(mainWindowHandler);
    //UpdateWindow(mainCommandHandler);

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

    return TRUE;
}
