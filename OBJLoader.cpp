#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include "OBJLoader.h"
#include "Texture.h"
#include <fstream>
#include <sstream>
#include <vector>

bool OBJLoader::load(const std::string& path, Mesh& mesh) {
    std::ifstream file(path);
    if (!file.is_open()) return false;

    std::vector<float> vx, vy, vz;
    std::vector<float> nx, ny, nz;
    std::vector<float> tx, ty;

    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string type;
        ss >> type;

        if (type == "v") {
            float x, y, z; ss >> x >> y >> z;
            vx.push_back(x); vy.push_back(y); vz.push_back(z);
        }
        else if (type == "vn") {
            float x, y, z; ss >> x >> y >> z;
            nx.push_back(x); ny.push_back(y); nz.push_back(z);
        }
        else if (type == "vt") {
            float u, v; ss >> u >> v;
            tx.push_back(u); ty.push_back(v);
        }
        else if (type == "f") {
            for (int i = 0; i < 3; i++) {
                std::string vert;
                ss >> vert;

                int v = 0, t = 0, n = 0;
                sscanf(vert.c_str(), "%d/%d/%d", &v, &t, &n);

                Vertex ver{};

                // vertex
                if (v > 0 && v <= vx.size()) {
                    ver.x = vx[v - 1];
                    ver.y = vy[v - 1];
                    ver.z = vz[v - 1];
                }

                // texture (ÞÏ Êßæä ÛíÑ ãæÌæÏÉ)
                if (t > 0 && t <= tx.size()) {
                    ver.u = tx[t - 1];
                    ver.v = 1.0f - ty[t - 1];
                }
                else {
                    ver.u = 0.0f;
                    ver.v = 0.0f;
                }

                // normal
                if (n > 0 && n <= nx.size()) {
                    ver.nx = nx[n - 1];
                    ver.ny = ny[n - 1];
                    ver.nz = nz[n - 1];
                }
                else {
                    ver.nx = 0.0f;
                    ver.ny = 1.0f;
                    ver.nz = 0.0f;
                }

                mesh.vertices.push_back(ver);
            }
        }

    }

    // äÍãøá texture æÇÍÏÉ ÝÞØ ãÈÏÆíðÇ
    mesh.textureID = Texture::load(
        "carOBJ/BRAKES.png"
    );

    return true;
}
