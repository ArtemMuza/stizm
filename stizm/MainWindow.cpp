#include "MainWindow.h"
#include "stizm.h"

MainWindow::MainWindow(HINSTANCE _hInstance) : hInstance(_hInstance){}

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
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        // TODO: Добавьте сюда любой код прорисовки, использующий HDC...
        EndPaint(hWnd, &ps);
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
        CW_USEDEFAULT, 0, 
        nullptr, 
        nullptr, 
        hInstance, 
        nullptr);

    if (!mainWindowHandler)
    {
        return FALSE;
    }

    ShowWindow(mainWindowHandler, SW_SHOW);
    UpdateWindow(mainWindowHandler);

    return TRUE;
	return 0;
}