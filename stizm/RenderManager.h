#pragma once
#include "framework.h"


class RenderManager
{
private:
	RenderManager() {};
	RenderManager(const RenderManager&) {};
	void operator=(const RenderManager&) {};


	void LoadShaders();
	void GenVABO();

public:
	int structWidth;
	int structHeight;
	static RenderManager& getInstance() {

		static RenderManager	rm_instance;
		return rm_instance;
	}

	GLvoid ChangeValues(int newWidth, int newHeight, int newStyle);
	
	int Init();
	int Shutdown();

	int shaderProgram;
	unsigned VAO, VBO;
	

	

	static void Render();
};

