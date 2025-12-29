#include "Camera.h"
#include <windows.h>    // Header File For Windows
#include <gl.h>      // Header File For The OpenGL32 Library
#include <glu.h>      // Header File For The GLu32 Library
#include <glaux.h>
#include "Collision.h"
#include "CollisionManager.h"
#include <iostream>


Camera::Camera()
{
   

    x = 0; z = -20; height = 1.8f; y = height; // «— ›«⁄  ﬁ—Ì»Ì ·≈‰”«‰
    yaw = 90.0f; pitch = 0;
    jumping = false;
    jumpTime = 0;
    jumpStartY = y;
}

void Camera::updateView()
{
    // Õ”«» «·« Ã«Â
    float dirX = cosf(yaw * 3.141 / 180.0f) * cosf(pitch * 3.141 / 180.0f);
    float dirY = sinf(pitch * 3.141 / 180.0f);
    float dirZ = sinf(yaw * 3.141 / 180.0f) * cosf(pitch * 3.141 / 180.0f);

    gluLookAt(
        x, y, z,
        x + dirX, y + dirY, z + dirZ,
        0.0f, 1.0f, 0.0f
    );
}

void Camera::moveForward(float distance)
{
    float newX = x + cosf(yaw * 3.141f / 180.0f) * distance;
    float newZ = z + sinf(yaw * 3.141f / 180.0f) * distance;

    AABB newPlayer;

    newPlayer.minX = newX - 0.3f;
    newPlayer.maxX = newX + 0.3f;

    newPlayer.minY = 0.0f;
    newPlayer.maxY = height;

    newPlayer.minZ = newZ - 0.3f;
    newPlayer.maxZ = newZ + 0.3f;

if (CollisionManager::canMove(newPlayer))
{
    x += cosf(yaw * 3.141 / 180.0f) * distance;
    z += sinf(yaw * 3.141 / 180.0f) * distance;
}



}

void Camera::moveBackward(float distance)
{
    moveForward(-distance);
}

void Camera::moveRight(float distance)
{
    float rad = (yaw + 90.0f) * 3.141f / 180.0f;

    float newX = x + cosf(rad) * distance;
    float newZ = z + sinf(rad) * distance;

    AABB newPlayer;

    newPlayer.minX = newX - 0.3f;
    newPlayer.maxX = newX + 0.3f;

    newPlayer.minY = 0.0f;
    newPlayer.maxY = height;

    newPlayer.minZ = newZ - 0.3f;
    newPlayer.maxZ = newZ + 0.3f;

    if (CollisionManager::canMove(newPlayer))
    {
        x = newX;
        z = newZ;
    }
}

void Camera::moveLeft(float distance)
{
    moveRight(-distance);
}

void Camera::jump()
{
    if (!jumping)
    {
        jumping = true;
        jumpTime = 0;
        jumpStartY = y;
    }
}

void Camera::shiftDown(float offset)
{
    y = height - offset;
}
