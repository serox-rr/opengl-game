module;
#include <FastNoise/FastNoise.h>
#include <glad/glad.h>
#include <glm/fwd.hpp>
#include <glm/glm.hpp>
#include <vector>
module engine;

namespace Engine {
    Vectors::Vectors(const glm::vec3 &color, const Shader &shader_, const std::vector<float> &vertex_) :
        Renderable(0, 0, color, glm::vec3(0, 0, 0), vertex_, shader_) {
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);
        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER,
                     sizeof(float) * vertex.size(),
                     &vertex[0],
                     GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
    }

    void Vectors::render() {
        shader.use();
        shader.setVec3("objectColor", color);
        glBindVertexArray(vao);
        glDrawArrays(GL_LINES, 0, vertex.size()/3);
    }

    Vectors::~Vectors() = default;
} // namespace Engine
