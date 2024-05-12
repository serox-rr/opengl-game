module;
#include <glad/glad.h>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/fwd.hpp>
#include <glm/glm.hpp>
#include <string>
module engine;
import :font;
import :renderable;
import :shader;

namespace Engine {
    Text::Text(std::string_view content_, const glm::vec3 &position_, const glm::vec3 &color_, const float scale_,
               Font &font_, Shader &shader_) :
        Renderable(0, 0, color_, position_, {}, shader_), content(content_), scale(scale_), font(font_) {
        glGenVertexArrays(1, &vao);
        glGenBuffers(1, &vbo);
        glBindVertexArray(vao);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, nullptr, GL_DYNAMIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), nullptr);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
        shader.use();
        glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(windows[0].getWidth()), 0.0f,
                                          static_cast<float>(windows[0].getHeight()));
        shader.setMat4("projection", projection);
    }


    void Text::render() const {
        shader.use();
        shader.setVec3("color", color);
        glActiveTexture(GL_TEXTURE0);
        glBindVertexArray(vao);
        auto xOffset = position.x;
        for (auto c = content.begin(); c != content.end(); ++c) {
            Character ch = font.getCharacters()[*c];

            const float xpos = xOffset + ch.bearing.x * scale;
            const float ypos = position.y - (ch.size.y - ch.bearing.y) * scale;

            const float w = ch.size.x * scale;
            const float h = ch.size.y * scale;
            const float vertices[6][4] = {
                    {xpos, ypos + h, 0.0f, 0.0f}, {xpos, ypos, 0.0f, 1.0f},     {xpos + w, ypos, 1.0f, 1.0f},

                    {xpos, ypos + h, 0.0f, 0.0f}, {xpos + w, ypos, 1.0f, 1.0f}, {xpos + w, ypos + h, 1.0f, 0.0f}};
            // render glyph texture over quad
            glBindTexture(GL_TEXTURE_2D, ch.textureID);
            // update content of VBO memory
            glBindBuffer(GL_ARRAY_BUFFER, vbo);
            glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            // render quad
            glDrawArrays(GL_TRIANGLES, 0, 6);
            // now advance cursors for next glyph (note that advance is number of 1/64 pixels)
            xOffset += (ch.advance >> 6) * scale; // bitshift by 6 to get value in pixels (2^6 = 64)
        }
        glBindVertexArray(0);
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    Text::~Text() = default;


    void Text::setContent(const std::string_view content_) { content = content_; }
} // namespace Engine
