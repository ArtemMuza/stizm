#pragma once
#include "framework.h"


class RenderManager
{
private:
	RenderManager() {};
	RenderManager(const RenderManager&) {};
	void operator=(const RenderManager&) {};

public:
	static RenderManager& getInstance() {

		static RenderManager	rm_instance;
		return rm_instance;
	}
	
	int Init();
	int Shutdown();

	static void Render();
};

