#include "Mesh.h"

void Mesh::draw() {
    if (textureID != 0)
    {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, textureID);
    }
    else
    {
        
    }

    glBegin(GL_TRIANGLES);
    for (auto& v : vertices) {
        glNormal3f(v.nx, v.ny, v.nz);
        glTexCoord2f(v.u, v.v);
        glVertex3f(v.x, v.y, v.z);
    }
    glEnd();

    glDisable(GL_TEXTURE_2D);
}
