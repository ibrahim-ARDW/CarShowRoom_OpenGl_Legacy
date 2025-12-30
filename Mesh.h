#pragma once
#include <vector>
#include <windows.h>    // Header File For Windows
#include <gl.h>      // Header File For The OpenGL32 Library
#include <glu.h>      // Header File For The GLu32 Library
#include <glaux.h>

struct Vertex {
    float x, y, z;
    float nx, ny, nz;
    float u, v;
};

class Mesh {
public:
    std::vector<Vertex> vertices;
    GLuint textureID = 0;

    void draw();
};

