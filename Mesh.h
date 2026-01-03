#pragma once
#include <windows.h>

#include <gl.h>      // Header File For The OpenGL32 Library
#include <glu.h>      // Header File For The GLu32 Library
#include <glaux.h>
#include <vector>
#include <string>


struct Mesh {
    std::vector<float> vertices;  // ‰ﬁ«ÿ «·„Ã”„
    std::vector<float> normals;   // « Ã«Â«  «·≈÷«¡…
    std::vector<float> texcoords; // ≈Õœ«ÀÌ«  «·’Ê—
    std::string materialName;
    float diffuseColor[3] = { 1.0f, 1.0f, 1.0f };
    GLuint textureID = 0;         // „⁄—› «·’Ê—… ›Ì OpenGL
    GLuint displayListID = 0;     // „⁄—› ﬁ«∆„… «·—”„ «·”—Ì⁄
};
