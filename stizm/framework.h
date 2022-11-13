// header.h: включаемый файл для стандартных системных включаемых файлов
// или включаемые файлы для конкретного проекта
//

#pragma once

#include "targetver.h"
#define WIN32_LEAN_AND_MEAN             // Исключите редко используемые компоненты из заголовков Windows
// Файлы заголовков Windows
#include <windows.h>
// Файлы заголовков среды выполнения C
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

#include <string>                   

#include <gl/glew.h>
#include <gl/gl.h>                                // Header File For The OpenGL32 Library
#include <gl/glu.h> 

#pragma comment (lib, "opengl32.lib")
#pragma comment (lib, "glu32.lib")

