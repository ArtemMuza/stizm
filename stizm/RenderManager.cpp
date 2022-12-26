#include "RenderManager.h"
#include "glm/glm.hpp"
//#include 
extern HDC* hDeviceContextGlobal;

const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec2 aPos;\n"
"layout (location = 1) in vec3 aColor;\n"

"out vec3 ourColor; \n"
"void main()\n"
"{\n"
"  gl_Position = vec4(aPos.x, aPos.y, 0.0, 1.0);\n"
" ourColor = aColor; \n"
"}\0";


const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"in vec3 ourColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(ourColor, 1.0f);\n"
"}\n\0";
#define widthGlobal RenderManager::getInstance().structWidth
#define heightGlobal RenderManager::getInstance().structHeight

unsigned** VAOs;
unsigned** VBOs;
int buff;
glm::vec3 prop(0.0f, 0.0f, 0.0f);
float* globalVertices, globalLines, globalPoints;
int style_of_drawing = 1;



float lines[] = {
     -0.5f,  0.0f, 0.0f,     0.0f,0.0f,0.0f,
      0.0f,  0.0f, 0.0f,     0.0f,0.0f,0.0f,

      0.0f,  0.0f, 0.0f,     0.0f,0.0f,0.0f,
     -0.25f, 0.45f, 0.0f,    0.0f,0.0f,0.0f,

     -0.5f,  0.0f, 0.0f,     0.0f,0.0f,0.0f,
     -0.25f, 0.45f, 0.0f,    0.0f,0.0f,0.0f,

     -0.5f,  0.0f, 0.0f,     0.0f,0.0f,0.0f,
     -0.25f, -0.45f, 0.0f,   0.0f,0.0f,0.0f,

      0.0f,  0.0f, 0.0f,     0.0f,0.0f,0.0f,
     -0.25f, -0.45f, 0.0f,   0.0f,0.0f,0.0f,

     -0.75f, -0.45f, 0.0f,	 0.0f,0.0f,0.0f,
     -0.5f,  0.0f, 0.0f,     0.0f,0.0f,0.0f,

     -0.75f, -0.45f, 0.0f,	 0.0f,0.0f,0.0f,
     -0.25f, -0.45f, 0.0f,    0.0f,0.0f,0.0f,

      0.0f,  0.0f, 0.0f,     0.0f,0.0f,0.0f,
      0.25f, 0.45f, 0.0f,    0.0f,0.0f,0.0f,

      0.25f, 0.45f, 0.0f,    0.0f,0.0f,0.0f,
     -0.25f, 0.45f, 0.0f,    0.0f,0.0f,0.0f,

      0.25f, 0.45f, 0.0f,    0.0f,0.0f,0.0f,
      0.7f, 0.2f, 0.0f,	     0.0f,0.0f,0.0f,

      0.7f, 0.2f, 0.0f,	     0.0f,0.0f,0.0f,
      0.45f, -0.25f, 0.0f,   0.0f,0.0f,0.0f,

      0.45f, -0.25f, 0.0f,   0.0f,0.0f,0.0f,
      0.0f,  0.0f, 0.0f,     0.0f,0.0f,0.0f,

     -0.25f, -0.45f, 0.0f,   0.0f,0.0f,0.0f,
      0.2f, -0.7f, 0.0f,     0.0f, 0.0f, 0.0f,

      0.2f, -0.7f, 0.0f,     0.0f, 0.0f, 0.0f,
      0.45f, -0.25f, 0.0f,   0.0f,0.0f,0.0f,
};

float vertices[] = {
        -0.5f,  0.0f, 0.0f,     1.0f,1.0f,0.0f,
        0.0f,  0.0f, 0.0f,     1.0f,1.0f,0.0f,
        -0.25f, 0.45f, 0.0f,      1.0f,1.0f,0.0f,

        0.0f,  0.0f, 0.0f,      1.0f,1.0f,1.0f,
        -0.25f, 0.45f, 0.0f,      1.0f,1.0f,1.0f,
        0.25f, 0.45f, 0.0f,       1.0f,1.0f,1.0f,

        -0.5f,  0.0f, 0.0f,     1.0f, 0.0f, 0.0f,
        -0.75f, -0.45f, 0.0f,	    1.0f, 0.0f, 0.0f,
        -0.25f, -0.45f, 0.0f,	    1.0f, 0.0f, 0.0f,

        -0.5f,  0.0f, 0.0f,     1.0f, 1.0f, 1.0f,
        -0.25f, -0.45f, 0.0f,	    1.0f, 1.0f, 1.0f,
        0.0f, 0.0f, 0.0f,		1.0f, 1.0f, 1.0f,

        0.7f, 0.2f, 0.0f,		0.0f, 1.0f, 0.0f,
        0.25f, 0.45f, 0.0f,		0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f,		0.0f, 1.0f, 0.0f,

        0.45f, -0.25f, 0.0f,  	0.0f, 1.0f, 0.0f,
        0.7f, 0.2f, 0.0f,		0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f,		0.0f, 1.0f, 0.0f,

        0.45f, -0.25f, 0.0f,	    0.6f, 0.0f, 0.6f,
        0.0f, 0.0f, 0.0f,		    0.6f, 0.0f, 0.6f,
        -0.25f, -0.45f, 0.0f,	    0.6f, 0.0f, 0.6f,

         0.45f, -0.25f, 0.0f,	    0.6f, 0.0f, 0.6f,
        -0.25f, -0.45f, 0.0f,	    0.6f, 0.0f, 0.6f,
         0.2f, -0.7f, 0.0f,		0.6f, 0.0f, 0.6f
};

float points[] = {
   -0.5f,   0.0f, 0.0f,   0.0f,0.0f,0.0f,

    0.0f,   0.0f, 0.0f,   0.0f,0.0f,0.0f,

   -0.25f,  0.45f, 0.0f,  0.0f,0.0f,0.0f,

    0.25f,  0.45f, 0.0f,  0.0f,0.0f,0.0f,

   -0.75f, -0.45f, 0.0f,  0.0f,0.0f,0.0f,

   -0.25f, -0.45f, 0.0f,  0.0f,0.0f,0.0f,
    
    0.45f, -0.25f, 0.0f,  0.0f,0.0f,0.0f,

    0.2f,  -0.7f, 0.0f,	  0.0f,0.0f,0.0f,

    0.7f, 0.2f, 0.0f,	  0.0f,0.0f,0.0f,

    0.45f, -0.25f, 0.0f,  0.0f,0.0f,0.0f,
};



GLvoid RenderManager::ChangeValues(int newWidth, int newHeight, int newStyle) {
    for (int i = 0; i < widthGlobal; i++) {
        delete[] VAOs[i];
        delete[] VBOs[i];
    }
    delete[] VAOs;
    delete[] VBOs;

    style_of_drawing = newStyle;

    widthGlobal = newWidth;
    heightGlobal = newHeight;
    buff = (widthGlobal >= heightGlobal ? widthGlobal : heightGlobal);
    VAOs = new unsigned* [widthGlobal];
    VBOs = new unsigned* [widthGlobal];

    for (int i = 0; i < widthGlobal; i++) {
        VAOs[i] = new unsigned[heightGlobal];
        VBOs[i] = new unsigned[heightGlobal];
    }

}

void GenVABOtemp(unsigned VAO, unsigned VBO, float* vertices, int size) {

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);



    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float)*size, vertices, GL_STATIC_DRAW);

    // Координатный атрибут
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Цветовой атрибут
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    //glBindBuffer(GL_ARRAY_BUFFER, 0);
    //glBindVertexArray(0);
}

int RenderManager::Init() {
    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
        //Todo: add logout
    }
  
    widthGlobal = 1;
    heightGlobal = 1;
   
    buff = (widthGlobal >= heightGlobal ? widthGlobal : heightGlobal);
    VAOs = new unsigned* [widthGlobal];
    VBOs = new unsigned* [widthGlobal];

    for (int i = 0; i < widthGlobal; i++) {
        VAOs[i] = new unsigned[heightGlobal];
        VBOs[i] = new unsigned[heightGlobal];
    }
    

   
    globalVertices = new float[]{ 
        -0.5f,  0.0f, 0.0f,         1.0f,1.0f,0.0f,
         0.0f,  0.0f, 0.0f,         1.0f,1.0f,0.0f,
        -0.25f, 0.45f, 0.0f,        1.0f,1.0f,0.0f,

        0.0f,  0.0f, 0.0f,          1.0f,1.0f,1.0f,
        -0.25f, 0.45f, 0.0f,        1.0f,1.0f,1.0f,
        0.25f, 0.45f, 0.0f,         1.0f,1.0f,1.0f,

        -0.5f,  0.0f, 0.0f,         1.0f, 0.0f, 0.0f,
        -0.75f, -0.45f, 0.0f,	    1.0f, 0.0f, 0.0f,
        -0.25f, -0.45f, 0.0f,	    1.0f, 0.0f, 0.0f,

        -0.5f,  0.0f, 0.0f,         1.0f, 1.0f, 1.0f,
        -0.25f, -0.45f, 0.0f,	    1.0f, 1.0f, 1.0f,
        0.0f, 0.0f, 0.0f,		    1.0f, 1.0f, 1.0f,

        0.45f, 0.2f, 0.0f,		    0.0f, 1.0f, 0.0f,
        0.25f, 0.45f, 0.0f,		    0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f,		    0.0f, 1.0f, 0.0f,

        0.45f, -0.25f, 0.0f,  	    0.0f, 1.0f, 0.0f,
        0.45f, 0.2f, 0.0f,		    0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f,		    0.0f, 1.0f, 0.0f,

        0.45f, -0.25f, 0.0f,	    0.6f, 0.0f, 0.6f,
        0.0f, 0.0f, 0.0f,		    0.6f, 0.0f, 0.6f,
        -0.25f, -0.45f, 0.0f,	    0.6f, 0.0f, 0.6f,

         0.45f, -0.25f, 0.0f,	    0.6f, 0.0f, 0.6f,
        -0.25f, -0.45f, 0.0f,	    0.6f, 0.0f, 0.6f,
         0.2f, -0.7f, 0.0f,		0.6f, 0.0f, 0.6f };
    //globalLines = new float[] {
    //    
    //};


    this->LoadShaders();
    //GenVABOtemp(LVAO, LVBO, lines);
    this->GenVABO();

    return true;
}

void RenderManager::Render() {
    
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    
    
    
   
    //GenVABOtemp();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   
    
        
        prop.x = 1/widthGlobal - 1/buff;
        prop.y = (0.25*heightGlobal/buff);

        if (style_of_drawing == 0) {
            for (int i = 0; i < widthGlobal; i++) {
                for (int j = 0; j < heightGlobal; j++) {
                    const int array_size = 180;
                    for (int k = 0; k < array_size; k = k + 6) {
                        globalVertices[k] = lines[k] / buff + prop.x + (0.95 * i - 0.5 * j) / buff;
                        globalVertices[k + 1] = lines[k + 1] / buff + prop.y + ((-0.25f) * i - 0.9f * j) / buff;

                        globalVertices[k + 3] = 0.0f;
                        globalVertices[k + 4] = 0.0f;
                        globalVertices[k + 5] = 0.0f;
                    }

                    GenVABOtemp(VAOs[i][j], VBOs[i][j], globalVertices, array_size);
                    glDrawArrays(GL_LINES, 0, array_size);
                }
            }

        }
        else if (style_of_drawing == 1) {
            for (int i = 0; i < widthGlobal; i++) {
                for (int j = 0; j < heightGlobal; j++) {
                    const int array_size = 144;
                    for (int k = 0; k < array_size; k = k + 6) {
                        globalVertices[k] = vertices[k] / buff + prop.x + (0.95 * i - 0.5 * j) / buff;
                        globalVertices[k + 1] = vertices[k + 1] / buff + prop.y + ((-0.25f) * i - 0.9f * j) / buff;

                        globalVertices[k + 3] = vertices[k + 3];
                        globalVertices[k + 4] = vertices[k + 4];
                        globalVertices[k + 5] = vertices[k + 5];
                    }

                    GenVABOtemp(VAOs[i][j], VBOs[i][j], globalVertices, array_size);
                    glDrawArrays(GL_TRIANGLES, 0, array_size);
                }
            }
        }
        else {
            for (int i = 0; i < widthGlobal; i++) {
                for (int j = 0; j < heightGlobal; j++) {
                    const int array_size = 60;
                    for (int k = 0; k < array_size; k = k + 6) {
                        globalVertices[k] = points[k] / buff + prop.x + (0.95 * i - 0.5 * j) / buff;
                        globalVertices[k + 1] = points[k + 1] / buff + prop.y + ((-0.25f) * i - 0.9f * j) / buff;

                        globalVertices[k + 3] = 0.0f;
                        globalVertices[k + 4] = 0.0f;
                        globalVertices[k + 5] = 0.0f;
                    }

                    GenVABOtemp(VAOs[i][j], VBOs[i][j], globalVertices, array_size);
                    glDrawArrays(GL_POINTS, 0, array_size);
                }
            }
        }

    SwapBuffers(*hDeviceContextGlobal);
}

void RenderManager::LoadShaders() {

    int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);


    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        //std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
    //    std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    this->shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        //std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void RenderManager::GenVABO() {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(lines), lines, GL_STATIC_DRAW);

    // Координатный атрибут
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Цветовой атрибут
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);
}

