#include "RenderManager.h"
#include "glm/glm.hpp"
extern HDC* hDeviceContextGlobal;

int RenderManager::Init() {
    glShadeModel(GL_SMOOTH);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    return true;
}

void RenderManager::Render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glClearColor(0, 0, 0, 0);

    glTranslatef(-0.9f, 0.0f, 0.0f);


    glm::vec3 arr2[6];
    arr2[0] = { 0.0f, 0.0f, 0.0f };
    arr2[1] = { 0.6f, 0.0f, 0.0f };
    arr2[2] = { 0.6f, 0.4f, 0.0f };
    arr2[3] = { 0.4f, 0.8f, 0.0f };
    arr2[4] = { 0.2f, 0.8f, 0.0f };
    arr2[5] = { 0.0f, 0.6f, 0.0f };

    glColor3f(1.0f, 1.0f, 1.0f);      // Установим цвет только один раз


    glBegin(GL_POINTS);
    for (int i = 0; i < 6; i++) {
        glVertex3f(arr2[i].x, arr2[i].y, arr2[i].z);
    }
    glEnd();
    
    glLoadIdentity();
  



    SwapBuffers(*hDeviceContextGlobal);
}