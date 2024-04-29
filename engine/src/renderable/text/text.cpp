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
    Text::Text(const std::string &content_, const glm::vec2 &position_, const glm::vec3 &color_, const float scale_,
               const Font &font_) :
        Renderable(0, 0), content(content_), position(position_), color(color_), scale(scale_), font(font_),
        shader(Shader("../../../engine/shaders/text/text.vert", "../../../engine/shaders/text/text.frag",
                      {"color", "projection"})) {
        unsigned int VBO;
        glGenVertexArrays(1, &vao);
        glGenBuffers(1, &VBO);
        glBindVertexArray(vao);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
        glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(windows[0].getWidth()), 0.0f,
                                          static_cast<float>(windows[0].getHeight()));
        shader.use();
        shader.setMat4("projection", projection);
    }


    void Text::render() {
        // activate corresponding render state
        shader.use();
        shader.setVec3("color", color);
        glActiveTexture(GL_TEXTURE0);
        glBindVertexArray(vao);

        // iterate through all characters
        std::string::const_iterator c;
        for (c = content.begin(); c != content.end(); c++) {
            Character ch = font.getCharacters()[*c];

            const float xpos = position.x + ch.bearing.x * scale;
            const float ypos = position.y - (ch.size.y - ch.bearing.y) * scale;

            const float w = ch.size.x * scale;
            const float h = ch.size.y * scale;
            // update VBO for each character
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
            position.x += (ch.advance >> 6) * scale; // bitshift by 6 to get value in pixels (2^6 = 64)
        }
        glBindVertexArray(0);
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    Text::~Text() = default;

} // namespace Engine
