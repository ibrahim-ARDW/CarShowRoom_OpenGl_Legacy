#include "Model_OBJ.h"
#include <fstream>
#include <sstream>

void Model_OBJ::LoadMTL(std::string folder, std::string filename) {
    std::ifstream file(folder + filename);
    if (!file.is_open()) return;

    std::string line, currentMat;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string cmd;
        ss >> cmd;
        if (cmd == "newmtl") {
            ss >> currentMat;
        }
        else if (cmd == "Kd") {
            ss >> materials[currentMat].r >> materials[currentMat].g >> materials[currentMat].b;
        }
    }
}

bool Model_OBJ::Load(const char* filename) {
    std::ifstream file(filename);
    if (!file.is_open()) return false;

    // ÊäÙíÝ ÇáÈíÇäÇÊ ÇáÓÇÈÞÉ Åä æÌÏÊ
    vertices.clear();
    normals.clear();
    faces.clear();

    std::string folder = filename;
    folder = folder.substr(0, folder.find_last_of("\\/") + 1);

    std::string line, currentMat = "default";
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string cmd;
        ss >> cmd;

        if (cmd == "v") {
            Vector3f v; ss >> v.x >> v.y >> v.z;
            vertices.push_back(v);
        }
        else if (cmd == "vn") {
            Vector3f vn; ss >> vn.x >> vn.y >> vn.z;
            normals.push_back(vn);
        }
        else if (cmd == "mtllib") {
            std::string mtlFile; ss >> mtlFile;
            LoadMTL(folder, mtlFile);
        }
        else if (cmd == "usemtl") {
            ss >> currentMat;
        }
        else if (cmd == "f") {
            Face face;
            face.matName = currentMat;
            std::string vertexStr;
            int count = 0;
            while (ss >> vertexStr && count < 4) {
                size_t firstSlash = vertexStr.find('/');
                size_t lastSlash = vertexStr.find_last_of('/');

                face.vIndices[count] = std::stoi(vertexStr.substr(0, firstSlash)) - 1;
                if (firstSlash != std::string::npos && firstSlash != lastSlash)
                    face.nIndices[count] = std::stoi(vertexStr.substr(lastSlash + 1)) - 1;
                else
                    face.nIndices[count] = -1;
                count++;
            }
            face.edgeCount = count;
            faces.push_back(face);
        }
    }

    // --- ßæÏ ÇáÊÓÑíÚ (Display List) ---
    // åäÇ äÞæã "ÈÊÓÌíá" ÚãáíÉ ÇáÑÓã ÏÇÎá ÐÇßÑÉ ßÑÊ ÇáÔÇÔÉ áãÑÉ æÇÍÏÉ ÝÞØ
    displayList = glGenLists(1);
    glNewList(displayList, GL_COMPILE);

    std::string lastMat = "";
    for (const auto& face : faces) {
        if (face.matName != lastMat) {
            lastMat = face.matName;
            if (materials.count(lastMat))
                glColor3f(materials[lastMat].r, materials[lastMat].g, materials[lastMat].b);
            else
                glColor3f(1.0f, 1.0f, 1.0f);
        }

        glBegin(face.edgeCount == 4 ? GL_QUADS : GL_TRIANGLES);
        for (int i = 0; i < face.edgeCount; i++) {
            if (face.nIndices[i] >= 0 && face.nIndices[i] < normals.size())
                glNormal3f(normals[face.nIndices[i]].x, normals[face.nIndices[i]].y, normals[face.nIndices[i]].z);

            if (face.vIndices[i] >= 0 && face.vIndices[i] < vertices.size())
                glVertex3f(vertices[face.vIndices[i]].x, vertices[face.vIndices[i]].y, vertices[face.vIndices[i]].z);
        }
        glEnd();
    }
    glEndList(); // ÅäåÇÁ ÇáÊÓÌíá

    return true;
}

void Model_OBJ::Draw() {
    // ÈÏáÇð ãä ÊßÑÇÑ ÂáÇÝ ÇáÃÓØÑ¡ äÓÊÏÚí ÇáÞÇÆãÉ ÇáãÓÌáÉ ÝÞØ
    glCallList(displayList);
}