
#include <iostream>
#include <windows.h>  
#include "LoadPngTexture.h"
#include <gl.h>      // Header File For The OpenGL32 Library
#include <glu.h>      // Header File For The GLu32 Library
#include <glaux.h>    // Header File For The Glaux Library
#include <cmath>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
GLuint LoadTexturePng::loadTexture(const char* filename){

        
            int width, height, channels;
            unsigned char* image = stbi_load(filename, &width, &height, &channels, STBI_rgb_alpha);

            if (!image) {
                std::cout << "Failed to load texture: " << filename << std::endl;
                return 0;
            }

            GLuint textureID;
            glGenTextures(1, &textureID);
            glBindTexture(GL_TEXTURE_2D, textureID);

            // ÊÍãíá ÇáÕæÑÉ Åáì OpenGL
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0,
                GL_RGBA, GL_UNSIGNED_BYTE, image);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            stbi_image_free(image);
            return textureID;
        }

	

