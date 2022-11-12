// stizm.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "stizm.h"
#include "WindowManager.h"
#include "RenderManager.h"


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);



    WindowManager* windManager = &WindowManager::getInstance();
    RenderManager* renderManager = &RenderManager::getInstance();
    windManager->Init(hInstance);

    windManager->CreateMainWindow();
    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_STIZM));
    MSG msg;
    
    renderManager->Init();
    // Цикл основного сообщения:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        glUseProgram(renderManager->shaderProgram);
        glBindVertexArray(renderManager->VAO);
        RenderManager::Render();
        
    }
   


    return (int) msg.wParam;
}


