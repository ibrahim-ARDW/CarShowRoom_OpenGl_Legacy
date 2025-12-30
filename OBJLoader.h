#pragma once

#include <string>
#include "Mesh.h"

class OBJLoader {
public:
    static bool load(const std::string& path, Mesh& mesh);
};

