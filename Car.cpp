#include "Car.h"
#include <cmath>

//  ⁄—Ì› «·„ €Ì—«  «·‹ Static
float Car::x = 0.0f;
float Car::y = -1.0f;
float Car::z = 0.0f;
float Car::angle = 10.0f;
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
    isDriven = !isDriven;

    if (isDriven)
    {
        cam.x = x;
        cam.z = z;
        cam.y = y + 6.0f; // ›Êﬁ «·”Ì«—…
    }
    else
    {
        cam.y = cam.height;
    }
}

void Car::updateDriving(bool keys[], Camera& cam) {
    if (!isDriven) return;

    const float moveSpeed = 0.05f;
    const float rotateSpeed = 1.5f;

    //  œÊÌ— «·”Ì«—… ›ﬁÿ
    if (keys[VK_LEFT])
        angle += rotateSpeed;

    if (keys[VK_RIGHT])
        angle -= rotateSpeed;

    //  ÕÊÌ· «·“«ÊÌ… ·—«œÌ«‰
    float rad = angle * 3.14159f / 180.0f;

    //  Õ—Ìﬂ «·”Ì«—… ··√„«„ Ê«·Œ·›
    if (keys[VK_UP])
    {
        x += sin(rad) * moveSpeed;
        z += cos(rad) * moveSpeed;
    }

    if (keys[VK_DOWN])
    {
        x -= sin(rad) * moveSpeed;
        z -= cos(rad) * moveSpeed;
    }

    // ? ·« ‰·„” «·ﬂ«„Ì—« Â‰«
}

void Car::draw() {
    glPushMatrix();
    glTranslatef(x, y, z);
    glRotatef(angle, 0, 1, 0);
    glScalef(0.6f, 0.6f, 0.6f);
    glColor3f(1.0f, 1.0f, 1.0f);
    for (auto& mesh : meshes) {
        if (mesh.displayListID) glCallList(mesh.displayListID);
    }
    glPopMatrix();
}