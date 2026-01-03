#pragma once
#include <string>
#include <vector>
#include <map>
#include <gl.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "Mesh.h"

class OBJLoader {
public:
    // ÇáÏÇáÉ ÇáÃÓÇÓíÉ áÊÍãíá ÇáãæÏíá
    static bool loadOBJ(const std::string& path, std::vector<Mesh>& meshes);

    // ÊÍæíá ÇáÈíÇäÇÊ áÜ Display Lists áÒíÇÏÉ ÇáÓÑÚÉ
    static void createDisplayLists(std::vector<Mesh>& meshes);

private:
    // ÏÇáÉ ãÓÇÚÏÉ áãÚÇáÌÉ ßá ÌÒÁ (Node) İí ÇáãæÏíá
    static void processNode(aiNode* node, const aiScene* scene, std::vector<Mesh>& meshes, std::string folder);

    // ÏÇáÉ ãÓÇÚÏÉ áÊÍæíá aiMesh ÇáÎÇÕ ÈÜ Assimp Åáì Mesh ÇáÎÇÕ ÈäÇ
    static Mesh processMesh(aiMesh* mesh, const aiScene* scene, std::string folder);
};
