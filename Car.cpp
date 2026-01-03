#include "Car.h"
#include <cmath>

// ÊÚÑíİ ÇáãÊÛíÑÇÊ ÇáÜ Static
float Car::x = 0.0f;
float Car::y = -1.0f;
float Car::z = 0.0f;
float Car::angle = 0.0f;
float Car::speed = 0.0f;
bool Car::isDriven = false;
std::vector<Mesh> Car::meshes;

bool Car::load(const std::string& path) {
    if (OBJLoader::loadOBJ(path, meshes)) {
        OBJLoader::createDisplayLists(meshes);
        return true;
    }
    return false;
}

void Car::mount(Camera& cam) {
    isDriven = !isDriven; // ÊÈÏíá ÇáÍÇáÉ
    if (isDriven) {
        // æÖÚ ÇáßÇãíÑÇ İí ãßÇä ÇáŞíÇÏÉ İæÑÇğ
        cam.x = x + 2.0f;
        cam.z = z + 2.0f;
        cam.y = y + 6.0f;
        cam.yaw = angle + 180.0f;
    }
    else {
        cam.y = cam.height; // ÅÚÇÏÉ ÇáØæá ÇáØÈíÚí ÚäÏ ÇáÎÑæÌ
    }
}

void Car::updateDriving(bool keys[], Camera& cam) {
    if (!isDriven) return;

    //// İíÒíÇÁ ÇáÍÑßÉ
    //if (keys[VK_UP])    speed += 0.005f;
    //if (keys[VK_DOWN])  speed -= 0.005f;
    //if (keys[VK_LEFT])  angle += 1.5f;
    //if (keys[VK_RIGHT]) angle -= 1.5f;

    //speed *= 0.95f; // ÇÍÊßÇß
    //x += sin(angle * 3.14159f / 180.0f) * speed;
    //z += cos(angle * 3.14159f / 180.0f) * speed;

    // ÊÍÏíË ÇáßÇãíÑÇ áÊÊÈÚ ÇáÓíÇÑÉ
    cam.x = x;
    cam.z = z;
   // cam.yaw = angle + 180.0f;
}

void Car::draw() {
    glPushMatrix();
    glTranslatef(x, y, z);
    glRotatef(angle, 0, 1, 0);
    glColor3f(1.0f, 1.0f, 1.0f);
    for (auto& mesh : meshes) {
        if (mesh.displayListID) glCallList(mesh.displayListID);
    }
    glPopMatrix();
}