#include "Car.h"
#include "OBJLoader.h"

bool Car::load() {
    return OBJLoader::load(
        "carOBJ/car.obj",
        mesh
    );
}

void Car::draw() {
    mesh.draw();
}
