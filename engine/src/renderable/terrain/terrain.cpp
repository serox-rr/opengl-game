module;
#include <FastNoise/FastNoise.h>
#include <glad/glad.h>
#include <glm/ext/matrix_transform.hpp>
#include <glm/fwd.hpp>
#include <glm/glm.hpp>
#include <vector>
module engine;

namespace Engine {
    Terrain::Terrain(const glm::vec3 &color, const Shader &shader_) :
        Renderable(0, 0, color, glm::vec3(0,0,0), {}, shader_), width(1000), height(1000), position(0,0,0) {
        GLuint ebo;
        const FastNoise::SmartNode<> fnGenerator = FastNoise::NewFromEncodedNodeTree("IgD2KLxApHA9PwcA");//
        std::vector<float> noiseOutput(width * height);
        fnGenerator->GenUniformGrid2D(noiseOutput.data(), 0, 0, width, height, 0.009f, 300);
        for (int i = 0; i < width; i++) {
            for (int j = 0; j < height; j++) {
                glm::vec3 p1(i * 10, noiseOutput[i * height + j] * 500, j * 10);
                const int widthOffset = (i != width - 1) * 2 - 1;
                glm::vec3 p2((i + widthOffset) * 10, noiseOutput[(i + widthOffset) * height + j] * 500, j * 10);
                const int heightOffset = (i != height - 1) * 2 - 1;
                glm::vec3 p3(i * 10, noiseOutput[i * height + (j + heightOffset)] * 500, (j + heightOffset) * 10);
                glm::vec3 normal = glm::abs(glm::normalize(glm::cross(p2 - p1, p3 - p1)));
                auto a = {p1.x, p1.y, p1.z, normal.x, normal.y, normal.z};
                vertex.insert(vertex.end(), a);
            }
        }
        std::vector<unsigned> indices = {};
        for (unsigned int i = 0; i < height - 1; i++) // for each row a.k.a. each strip
        {
            for (unsigned int j = 0; j < width; j++) // for each column
            {
                for (unsigned int k = 0; k < 2; k++) // for each side of the strip
                {
                    indices.push_back(j + width * (i + k));
                }
            }
        }
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);
        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER,
                     vertex.size() * sizeof(float), // size of vertices buffer
                     &vertex[0], // pointer to first element
                     GL_STATIC_DRAW);

        // position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
        glEnableVertexAttribArray(0);
        // Normals
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        glGenBuffers(1, &ebo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                     indices.size() * sizeof(unsigned int), // size of indices buffer
                     &indices[0], // pointer to first element
                     GL_STATIC_DRAW);
    }

    void Terrain::render() {
        shader.use();
        shader.setVec3("objectColor", color);
        // draw mesh
        glBindVertexArray(vao);
        // render the mesh triangle strip by triangle strip - each row at a time
        for (unsigned int strip = 0; strip < width - 1; ++strip) {
            glDrawElements(GL_TRIANGLE_STRIP, // primitive type
                           height * 2, // number of indices to render
                           GL_UNSIGNED_INT, // index data type
                           (void *)(sizeof(unsigned int) * height * 2 * strip)); // offset to starting index
        }
    }

    Terrain::~Terrain() = default;
} // namespace Engine
