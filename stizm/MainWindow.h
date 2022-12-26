#pragma once
#include "framework.h"
#include "RenderManager.h"
#define mainWindowName	L"MainWindow"
#define mainMenuName	L"MainMenu"


class MainWindow
{
private:
	HINSTANCE hInstance =  NULL ;
	HINSTANCE hMenuInstance = NULL;

	HWND mainWindowHandler =  NULL ;
	HWND mainMenuHandler = NULL;

	WNDCLASSEXW mainWindowClass = { NULL };
	WNDCLASSEXW mainMenuClass = { NULL };

	HGLRC  hRenderContext = NULL;                           // Permanent Rendering Context
	HDC    hDeviceContext = NULL;


	ATOM Register();
public:
	
	MainWindow(HINSTANCE _hInstance);
	static LRESULT mainWindowProcedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	static LRESULT mainMenuProcedure(HWND hWnd, UINT message, WPARAM wParame, LPARAM lParam);

	static GLvoid ResizeWindow(GLsizei width, GLsizei height);          // Resize And Initialize The GL Window

	int Create();
	GLvoid Destroy();

	int CreateContext();
};

