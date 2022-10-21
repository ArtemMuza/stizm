#pragma once

#include "framework.h"

enum messageTypes { 
	Exclamation = MB_ICONEXCLAMATION,
	Information = MB_ICONINFORMATION,
	Error = MB_ICONERROR
};

class WindowManager
{

	WindowManager() {}
	WindowManager(const WindowManager&) {}
	void operator=(const WindowManager&) {}
public:

	static WindowManager* getInstance() {

		static WindowManager	wm_instance;
		return &wm_instance;
	}

	int Init();
	int Shutdown();

	int CreateMainWindow();
	

	static int Message(std::string _msg, std::string _title, messageTypes _type = Exclamation);
	static int Message(std::string _msg, messageTypes _type = Exclamation);
};

