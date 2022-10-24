#pragma once
#include "framework.h"
#define mainWindowName L"MainWindow"
class MainWindow
{
private:
	HINSTANCE hInstance =  NULL ;
	HWND mainWindowHandler =  NULL ;
	HGLRC  hRenderContext = NULL;                           // Permanent Rendering Context
	HDC    hDeviceContext = NULL;
	WNDCLASSEXW mainWindowClass = { NULL };

	ATOM Register();
	int InitGL();
public:
	MainWindow(HINSTANCE _hInstance);
	static LRESULT mainWindowProcedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	static GLvoid ResizeWindow(GLsizei width, GLsizei height);          // Resize And Initialize The GL Window
	
	static int DrawGLScene();
	
	int Create();
	GLvoid Destroy();

	int CreateContext();
};

