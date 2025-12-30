#include <windows.h>    // Header File For Windows
#include <gl.h>      // Header File For The OpenGL32 Library
#include <glu.h>      // Header File For The GLu32 Library
#include <glaux.h>    // Header File For The Glaux Library
#include <cmath>
//#include <stb_image.h>
#include <iostream>
#include "DrawAllShapes.h"
#include "Collision.h"

void DrawShapes::drawMountains(GLuint texture)
{
    glBindTexture(GL_TEXTURE_2D, texture);

    float size = 50.0f;  // ‰›” ÕÃ„ «·√—÷
    float height = 25.0f; // «— ›«⁄ «·Ã»«·
    float repeat = 1.0f;  //  ﬂ—«— Texture

    // ===== Œ·›Ì… =====
    glBegin(GL_QUADS);
    glTexCoord2f(1, 1); glVertex3f(-size, -1.0f, size );  // √»⁄œ ﬁ·Ì·« „‰ «·√—÷
    glTexCoord2f(0, 1); glVertex3f(size, -1.0f, size );
    glTexCoord2f(0, 0); glVertex3f(size, height, size );
    glTexCoord2f(1, 0); glVertex3f(-size, height, size );
    glEnd();

    // ===== √„«„Ì… =====
    glBegin(GL_QUADS);
    glTexCoord2f(1, 1); glVertex3f(-size, -1.0f, -size );
    glTexCoord2f(0, 1); glVertex3f(size, -1.0f, -size );
    glTexCoord2f(0, 0); glVertex3f(size, height, -size );
    glTexCoord2f(1, 0); glVertex3f(-size, height, -size );
    glEnd();

    // ===== Ì”«— =====
    glBegin(GL_QUADS);
    glTexCoord2f(1, 1); glVertex3f(-size , -1.0f, -size);
    glTexCoord2f(0, 1); glVertex3f(-size , -1.0f, size);
    glTexCoord2f(0, 0); glVertex3f(-size, height, size);
    glTexCoord2f(1, 0); glVertex3f(-size , height, -size);
    glEnd();

    // ===== Ì„Ì‰ =====
    glBegin(GL_QUADS);
    glTexCoord2f(1, 1); glVertex3f(size , -1.0f, -size);
    glTexCoord2f(0,1); glVertex3f(size , -1.0f, size);
    glTexCoord2f(0, 0); glVertex3f(size , height, size);
    glTexCoord2f(1, 0); glVertex3f(size , height, -size);
    glEnd();
}

void DrawShapes::drawFloor(GLuint texture)
{
   
    glBindTexture(GL_TEXTURE_2D, texture);

    glBegin(GL_QUADS);

    float size = 400.0f;
    float repeat = 200.0f;

    glTexCoord2f(0.0f, 0.0f);       glVertex3f(-size, -1.0f, -size);
    glTexCoord2f(repeat, 0.0f);     glVertex3f(size, -1.0f, -size);
    glTexCoord2f(repeat, repeat);   glVertex3f(size, -1.0f, size);
    glTexCoord2f(0.0f, repeat);     glVertex3f(-size, -1.0f, size);

    glEnd();
}
void DrawShapes::drawHouse(GLuint texture)
{
   
}
void DrawShapes::DrawDoor(GLuint doorTex)
{
    glBindTexture(GL_TEXTURE_2D, doorTex);


    float w = 3.0f;
    float h = 4.0f;

    glBegin(GL_QUADS);

    glTexCoord2f(0, 0); glVertex3f(0, 0, 0);
    glTexCoord2f(1, 0); glVertex3f(w, 0, 0);
    glTexCoord2f(1, 1); glVertex3f(w, h, 0);
    glTexCoord2f(0, 1); glVertex3f(0, h, 0);

    glEnd();

  
}

