#include <windows.h>    // Header File For Windows

#include <gl.h>      // Header File For The OpenGL32 Library
#include <glu.h>      // Header File For The GLu32 Library
#include <glaux.h>
#include "OBJLoader.h"

#include "LoadPngTexture.h"
#include "LoadTGA.h"
#include <iostream>

bool OBJLoader::loadOBJ(const std::string& path, std::vector<Mesh>& meshes) {
    Assimp::Importer importer;

    // «·≈⁄œ«œ« : Triangulate ( ÕÊÌ· ·„À·À« )° FlipUVs ( ’ÕÌÕ « Ã«Â «·’Ê—)° GenSmoothNormals ( Ê·Ìœ ≈÷«¡… ‰«⁄„…)
    const aiScene* scene = importer.ReadFile(path,
        aiProcess_Triangulate |
        aiProcess_FlipUVs |
        aiProcess_GenSmoothNormals);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        std::cout << "Assimp Error: " << importer.GetErrorString() << std::endl;
        return false;
    }

    std::string folder = path.substr(0, path.find_last_of("/\\"));
    processNode(scene->mRootNode, scene, meshes, folder);

    return true;
}

void OBJLoader::processNode(aiNode* node, const aiScene* scene, std::vector<Mesh>& meshes, std::string folder) {
    // „⁄«·Ã… ﬂ· «·‹ Meshes «·„ÊÃÊœ… ›Ì «·‰Êœ «·Õ«·Ì…
    for (unsigned int i = 0; i < node->mNumMeshes; i++) {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        meshes.push_back(processMesh(mesh, scene, folder));
    }
    //  ﬂ—«— «·⁄„·Ì… ·ﬂ· «·√»‰«¡ («·ﬁÿ⁄ «·›—⁄Ì… ··”Ì«—…)
    for (unsigned int i = 0; i < node->mNumChildren; i++) {
        processNode(node->mChildren[i], scene, meshes, folder);
    }
}

Mesh OBJLoader::processMesh(aiMesh* mesh, const aiScene* scene, std::string folder) {
    Mesh myMesh;

    // 1. «” Œ—«Ã «·‰ﬁ«ÿ° «·‰Ê—„«·“° Ê«· ﬂ” ‘—
    for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
        myMesh.vertices.push_back(mesh->mVertices[i].x);
        myMesh.vertices.push_back(mesh->mVertices[i].y);
        myMesh.vertices.push_back(mesh->mVertices[i].z);

        if (mesh->HasNormals()) {
            myMesh.normals.push_back(mesh->mNormals[i].x);
            myMesh.normals.push_back(mesh->mNormals[i].y);
            myMesh.normals.push_back(mesh->mNormals[i].z);
        }

        if (mesh->mTextureCoords[0]) {
            myMesh.texcoords.push_back(mesh->mTextureCoords[0][i].x);
            myMesh.texcoords.push_back(mesh->mTextureCoords[0][i].y);
        }
    }

    // 2. „⁄«·Ã… «·„«œ… («··Ê‰ Ê«· ﬂ” ‘—)
    if (mesh->mMaterialIndex >= 0) {
        aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

        // √. „Õ«Ê·… «” Œ—«Ã «· ﬂ” ‘— («·’Ê—…)
        aiString str;
        if (material->GetTexture(aiTextureType_DIFFUSE, 0, &str) == AI_SUCCESS) {
            std::string texPath = folder + "/" + str.C_Str();
            if (texPath.find(".png") != std::string::npos)
                myMesh.textureID = LoadTexturePng::loadTexture(texPath.c_str());
            else if (texPath.find(".tga") != std::string::npos)
                myMesh.textureID = LoadTga::LoadTGA(texPath.c_str());
        }

        // ». «” Œ—«Ã «··Ê‰ «·Œ«„ (Diffuse Color) - Â–« „« ”ÌÕ· „‘ﬂ·… «·»Ì«÷
        aiColor3D color(1.0f, 1.0f, 1.0f);
        if (material->Get(AI_MATKEY_COLOR_DIFFUSE, color) == AI_SUCCESS) {
            myMesh.diffuseColor[0] = color.r;
            myMesh.diffuseColor[1] = color.g;
            myMesh.diffuseColor[2] = color.b;
        }
    }

    return myMesh;
}

//void OBJLoader::createDisplayLists(std::vector<Mesh>& meshes) {
//    for (auto& mesh : meshes) {
//        mesh.displayListID = glGenLists(1);
//        glNewList(mesh.displayListID, GL_COMPILE);
//
//       
//        if (mesh.textureID != 0) {
//            glEnable(GL_TEXTURE_2D);
//            glBindTexture(GL_TEXTURE_2D, mesh.textureID);
//        }
//        else {
//            glDisable(GL_TEXTURE_2D);
//           
//        }
//
//        glBegin(GL_TRIANGLES);
//        for (size_t i = 0; i < mesh.vertices.size() / 3; i++) {
//            if (!mesh.normals.empty())
//                glNormal3f(mesh.normals[i * 3 + 0], mesh.normals[i * 3 + 1], mesh.normals[i * 3 + 2]);
//
//            if (!mesh.texcoords.empty())
//                glTexCoord2f(mesh.texcoords[i * 2 + 0], mesh.texcoords[i * 2 + 1]);
//
//            glVertex3f(mesh.vertices[i * 3 + 0], mesh.vertices[i * 3 + 1], mesh.vertices[i * 3 + 2]);
//        }
//        glEnd();
//        glDisable(GL_TEXTURE_2D);
//        glEndList();
//    }
//}
void OBJLoader::createDisplayLists(std::vector<Mesh>& meshes) {
    for (auto& mesh : meshes) {
        mesh.displayListID = glGenLists(1);
        glNewList(mesh.displayListID, GL_COMPILE);

        if (mesh.textureID != 0) {
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, mesh.textureID);
            glColor3f(1.0f, 1.0f, 1.0f); // √»Ì÷ ·ﬂÌ ÌŸÂ— «· ﬂ” ‘— »·Ê‰Â «·√’·Ì
        }
        else {
            glDisable(GL_TEXTURE_2D);
            //  ÿ»Ìﬁ «··Ê‰ «·Œ«„ «·„” Œ—Ã „‰ „·› «·‹ MTL
            glColor3f(mesh.diffuseColor[0], mesh.diffuseColor[1], mesh.diffuseColor[2]);
        }

        glBegin(GL_TRIANGLES);
        for (size_t i = 0; i < mesh.vertices.size() / 3; i++) {
            if (!mesh.normals.empty())
                glNormal3f(mesh.normals[i * 3 + 0], mesh.normals[i * 3 + 1], mesh.normals[i * 3 + 2]);
            if (!mesh.texcoords.empty())
                glTexCoord2f(mesh.texcoords[i * 2 + 0], mesh.texcoords[i * 2 + 1]);
            glVertex3f(mesh.vertices[i * 3 + 0], mesh.vertices[i * 3 + 1], mesh.vertices[i * 3 + 2]);
        }
        glEnd();

        glDisable(GL_TEXTURE_2D);
        glEndList();
    }
}