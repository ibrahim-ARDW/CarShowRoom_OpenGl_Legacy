#pragma once
#include <windows.h>
#include <gl.h>
#include <glu.h>
#include <cstdio>

class LoadTga {
public:
    static GLuint LoadTGA(const char* filename);
};

