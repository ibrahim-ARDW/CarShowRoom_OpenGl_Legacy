#pragma once
#include <vector>
#include "Mesh.h"
#include "OBJLoader.h"
#include "Camera.h"

class Car {
public:
    // ãÊÛíÑÇÊ ÇáÍÇáÉ (Static áÓåæáÉ ÇáæÕæá)
    static float x, y, z;
    static float angle, speed;
    static bool isDriven;
    static std::vector<Mesh> meshes;

    // æÙÇÆİ ÇáÊÍßã
    static bool load(const std::string& path);
    static void draw();

    // ÏÇáÉ ÇáŞíÇÏÉ ÇáÊí ÓÊÓÊÏÚíåÇ İí ÍáŞÉ ÇáÜ Update
    static void updateDriving(bool keys[], Camera& cam);

    // ÏÇáÉ ÇáÇäÊŞÇá ááßÇãíÑÇ ÇáÊí ÓÊÓÊÏÚíåÇ ÚäÏ ÖÛØ E
    static void mount(Camera& cam);
};