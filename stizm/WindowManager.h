#pragma once

#include "framework.h"

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

	int Message(std::string _msg, int _type);
};

