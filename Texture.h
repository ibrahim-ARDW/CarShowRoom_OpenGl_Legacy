#pragma once
#include <windows.h>    // Header File For Windows
#include <gl.h>      // Header File For The OpenGL32 Library
#include <glu.h>      // Header File For The GLu32 Library
#include <glaux.h>
#include <string>

class Texture {
public:
    static GLuint load(const std::string& path);
};

