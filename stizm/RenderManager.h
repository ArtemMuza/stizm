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
	static RenderManager& getInstance() {

		static RenderManager	rm_instance;
		return rm_instance;
	}
	
	int Init();
	int Shutdown();

	int shaderProgram;
	unsigned VAO, VBO;

	float vertices[9] = {
	   -0.5f, -0.5f, 0.0f, // левая вершина
		0.5f, -0.5f, 0.0f, // правая вершина
		0.0f,  0.5f, 0.0f  // верхняя вершина   
	};

	static void Render();
};

