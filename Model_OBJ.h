#ifndef MODEL_OBJ_H
#define MODEL_OBJ_H

#include <windows.h>
#include <gl.h>      // Header File For The OpenGL32 Library
#include <glu.h>      // Header File For The GLu32 Library
#include <glaux.h>
#include <vector>
#include <string>
#include <map>

struct Vector3f { float x, y, z; };

struct Material {
    float r, g, b; // «·√·Ê«‰ ›ﬁÿ
};

struct Face {
    int vIndices[4];
    int nIndices[4];
    int edgeCount;
    std::string matName;
};

class Model_OBJ {
public:
    GLuint displayList; // √÷› Â–« «·„ €Ì—
    bool Load(const char* filename);
    void Draw();

private:
    void LoadMTL(std::string folder, std::string filename);
    std::vector<Vector3f> vertices;
    std::vector<Vector3f> normals;
    std::vector<Face> faces;
    std::map<std::string, Material> materials;
};

#endif