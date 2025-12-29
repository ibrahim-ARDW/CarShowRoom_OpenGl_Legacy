#pragma once
#include <cmath>
#include <windows.h>    // Header File For Windows
#include <gl.h>      // Header File For The OpenGL32 Library
#include <glu.h>      // Header File For The GLu32 Library
#include <glaux.h>
#include "Collision.h"

class Camera
{
public:
    // „Êﬁ⁄ «·ﬂ«„Ì—«
    float x, y, z;
  
  //  AABB newPlayer;
    // « Ã«Â «·‰Ÿ—
    float yaw;    // √›ﬁÌ
    float pitch;  // —√”Ì

    // «— ›«⁄ «·ﬂ«„Ì—« «·ÿ»Ì⁄Ì
    float height;

    // Õ«·«  «·Õ—ﬂ…
    bool jumping;
    float jumpStartY;
    float jumpTime;

    Camera();

    void moveForward(float distance);
    void moveBackward(float distance);
    void moveRight(float distance);
    void moveLeft(float distance);
    void updateView();  //  ÿ»ﬁ gluLookAt

    void jump();   // »œ«Ì… «·ﬁ›“
    void shiftDown(float offset); // «·«‰Œ›«÷ ⁄‰œ Shift
};

