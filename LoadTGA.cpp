#include <windows.h>
#include <gl.h>      // Header File For The OpenGL32 Library
#include <glu.h>      // Header File For The GLu32 Library
#include <glaux.h>
#include <cstdio>
#include "LoadTGA.h"

GLuint LoadTga::LoadTGA(const char* filename) {
    FILE* file = fopen(filename, "rb");
    if (!file) return 0;

    unsigned char header[18];
    fread(header, 1, 18, file);

    int width = header[12] + (header[13] << 8);
    int height = header[14] + (header[15] << 8);
    int bpp = header[16];

    int size = width * height * (bpp / 8);
    unsigned char* data = new unsigned char[size];
    fread(data, 1, size, file);
    fclose(file);

    // BGR ? RGB
    for (int i = 0; i < size; i += (bpp / 8)) {
        unsigned char temp = data[i];
        data[i] = data[i + 2];
        data[i + 2] = temp;
    }

    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(
        GL_TEXTURE_2D,
        0,
        (bpp == 32) ? GL_RGBA : GL_RGB,
        width,
        height,
        0,
        (bpp == 32) ? GL_RGBA : GL_RGB,
        GL_UNSIGNED_BYTE,
        data
    );

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    delete[] data;
    return texture;
}