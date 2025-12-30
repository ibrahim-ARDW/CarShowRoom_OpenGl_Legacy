#pragma once
#include "Mesh.h"

class Car {
public:
    bool load();
    void draw();
private:
    Mesh mesh;
};

