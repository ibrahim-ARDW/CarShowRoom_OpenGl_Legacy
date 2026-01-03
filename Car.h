#pragma once
#include <vector>
#include "Mesh.h"
#include "OBJLoader.h"
#include "Camera.h"

class Car {
public:
    // ÇáæÖÚ æÇáãßÇä
    float x, y, z;
    float angle;
    float speed;
    bool isDriven; // åá ÇááÇÚÈ ÏÇÎá ÇáÓíÇÑÉ¿

    std::vector<Mesh> meshes;

    Car();
    bool load(const std::string& path);

    // ÏÇáÉ ÇáÊÍÏíË ÊÃÎĞ ãÑÌÚ ááßÇãíÑÇ áÊÊÍßã ÈåÇ ÚäÏ ÇáŞíÇÏÉ
    void update(bool keys[], Camera& cam);

    // ÏÇáÉ ÇáÑÓã
    void draw();

    // ÏÇáÉ ááÊÍŞŞ ãä ÇáãÓÇİÉ Èíä ÇáßÇãíÑÇ æÇáÓíÇÑÉ
    bool isPlayerNear(float camX, float camZ);
};
