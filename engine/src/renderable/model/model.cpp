module;
#include <algorithm>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stdexcept>
module engine;

namespace Engine {
    Model::Model(const std::string &path_, const glm::vec3 &position_, Shader &shader_) :
        shader(shader_), path(path_), directory(path.substr(0, path.find_last_of('/'))), meshes({}), texturesLoaded({}),
        position(position_) {
        Assimp::Importer importer;
        const aiScene *scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

        if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
            throw std::runtime_error("ERROR::ASSIMP::" + std::string(importer.GetErrorString()));
        }
        processNode(scene->mRootNode, scene);
    }

    void Model::render() const {
        std::ranges::for_each(meshes.begin(), meshes.end(), [](const Mesh &mesh) { mesh.render(); });
    }

    void Model::processNode(const aiNode *node, const aiScene *scene) {
        for (unsigned int i = 0; i < node->mNumMeshes; i++) {
            const aiMesh *aiMeshElt = scene->mMeshes[node->mMeshes[i]];
            meshes.push_back(processMesh(aiMeshElt, scene));
        }
        for (unsigned int i = 0; i < node->mNumChildren; i++) {
            processNode(node->mChildren[i], scene);
        }
    }

    Mesh Model::processMesh(const aiMesh *mesh, const aiScene *scene) {
        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;
        std::vector<ModelTexture> textures;

        for (unsigned i = 0; i < mesh->mNumVertices; i++) {
            vertices.push_back({.Position = {mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z},
                                .Normal = {mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z},
                                .TexCoords = mesh->mTextureCoords[0] ? glm::vec2(mesh->mTextureCoords[0][i].x,
                                                                                 mesh->mTextureCoords[0][i].y)
                                                                     : glm::vec2(0.0f)});
        }
        for (unsigned i = 0; i < mesh->mNumFaces; i++) {
            const aiFace face = mesh->mFaces[i];
            for (unsigned j = 0; j < face.mNumIndices; j++)
                indices.push_back(face.mIndices[j]);
        }
        // process material
        const aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
        auto diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
        textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
        auto specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
        textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
        return Mesh(vertices, indices, textures, shader);
    }

    std::vector<ModelTexture> Model::loadMaterialTextures(const aiMaterial *mat, const aiTextureType type,
                                                          const std::string &typeName) {
        std::vector<ModelTexture> textures;
        for (unsigned int i = 0; i < mat->GetTextureCount(type); i++) {
            aiString str;
            mat->GetTexture(type, i, &str);
            bool skip = false;
            std::ranges::for_each(texturesLoaded.begin(), texturesLoaded.end(), [&](const ModelTexture &texture) {
                if (std::strcmp(texture.path.c_str(), str.C_Str()) == 0) {
                    textures.push_back(texture);
                    skip = true;
                }
            });
            if (!skip) { // if texture hasn't been loaded already, load it
                ModelTexture texture{
                        .id = TextureFromFile(str.C_Str(), directory), .type = typeName, .path = str.C_Str()};
                textures.push_back(texture);
                texturesLoaded.push_back(texture); // add to loaded textures
            }
        }
        return textures;
    }

    const glm::vec3 &Model::getPosition() const { return position; }

    const Shader &Model::getShader() const { return shader; }
} // namespace Engine
