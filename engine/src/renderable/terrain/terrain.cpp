module;
#include <FastNoise/FastNoise.h>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>
module engine;

namespace Engine {
    Terrain::Terrain(const glm::vec3 &color, const Shader &shader_) :
        Renderable(0, 0, color, glm::vec3(0, 0, 0), {}, shader_), width(1000), height(1000), rez(20), position(0, 0, 0),
        heightMap(width * height) {

        const FastNoise::SmartNode<> fnGenerator = FastNoise::NewFromEncodedNodeTree("HAABGQAHAAAAAIA/AAAAAEA=");
        fnGenerator->GenUniformGrid2D(heightMap.data(), 0, 0, width, height, 0.009f, 300);
        unsigned int texture;
        glGenTextures(1, &texture);
        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, width, height, 0, GL_RED, GL_FLOAT, heightMap.data());
        glGenerateMipmap(GL_TEXTURE_2D);

        Texture grass("../../../game/resources/materials/grass/001/Grass001_2K-JPG_Color.jpg", GL_TEXTURE1, "jpg");

        shader.use();
        shader.setInt("heightMap", 2);
        shader.setVec3("material.ambient", glm::vec3(0.1, 0.1, 0.1));
        shader.setVec3("material.diffuse", glm::vec3(0.4, 0.7, 0.2));
        shader.setVec3("material.specular", glm::vec3(0.1, 0.1, 0.1));
        shader.setFloat("material.shininess", 10);
        shader.setVec3("light.direction", glm::vec3(-0.2f, -1.0f, -0.3f));
        shader.setVec3("light.ambient", glm::vec3(0.1, 0.1, 0.1));
        shader.setVec3("light.diffuse", glm::vec3(0.5, 0.5, 0.5));
        shader.setVec3("light.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        for (unsigned i = 0; i <= rez - 1; i++) {
            for (unsigned j = 0; j <= rez - 1; j++) {
                vertices.push_back(-width / 2.0f + width * i / static_cast<float>(rez)); // v.x
                vertices.push_back(0.0f); // v.y
                vertices.push_back(-height / 2.0f + height * j / static_cast<float>(rez)); // v.z
                vertices.push_back(i / static_cast<float>(rez)); // u
                vertices.push_back(j / static_cast<float>(rez)); // v

                vertices.push_back(-width / 2.0f + width * (i + 1) / static_cast<float>(rez)); // v.x
                vertices.push_back(0.0f); // v.y
                vertices.push_back(-height / 2.0f + height * j / static_cast<float>(rez)); // v.z
                vertices.push_back((i + 1) / static_cast<float>(rez)); // u
                vertices.push_back(j / static_cast<float>(rez)); // v

                vertices.push_back(-width / 2.0f + width * i / static_cast<float>(rez)); // v.x
                vertices.push_back(0.0f); // v.y
                vertices.push_back(-height / 2.0f + height * (j + 1) / static_cast<float>(rez)); // v.z
                vertices.push_back(i / static_cast<float>(rez)); // u
                vertices.push_back((j + 1) / static_cast<float>(rez)); // v

                vertices.push_back(-width / 2.0f + width * (i + 1) / static_cast<float>(rez)); // v.x
                vertices.push_back(0.0f); // v.y
                vertices.push_back(-height / 2.0f + height * (j + 1) / static_cast<float>(rez)); // v.z
                vertices.push_back((i + 1) / static_cast<float>(rez)); // u
                vertices.push_back((j + 1) / static_cast<float>(rez)); // v
            }
        }

        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);
        // glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );

        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

        // position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
        glEnableVertexAttribArray(0);
        // texCoord attribute
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(sizeof(float) * 3));
        glEnableVertexAttribArray(1);

        glPatchParameteri(GL_PATCH_VERTICES, 4);
    }

    void Terrain::render() {
        // draw mesh
        glBindVertexArray(vao);
        glDrawArrays(GL_PATCHES, 0, 4 * rez * rez);
    }

    Terrain::~Terrain() = default;

    const std::vector<float> &Terrain::getHeightMap() const { return heightMap; }

    const int &Terrain::getWidth() const { return width; }

    const int &Terrain::getHeight() const { return height; }

    const int &Terrain::getRez() const { return rez; }
} // namespace Engine
