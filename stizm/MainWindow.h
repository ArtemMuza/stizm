#pragma once
#include "framework.h"
#define mainWindowName L"MainWindow"
class MainWindow
{
private:
	HINSTANCE hInstance =  NULL ;
	HWND mainWindowHandler =  NULL ;
	WNDCLASSEXW mainWindowClass = { NULL };

	ATOM Register();

public:
	MainWindow(HINSTANCE _hInstance);
	static LRESULT mainWindowProcedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	int Create();
};

