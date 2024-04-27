module;
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <ft2build.h>
#include <stdexcept>
#include <filesystem>
#include <iostream>
#include <glm/vec2.hpp>

#include FT_FREETYPE_H
module engine;

namespace Engine {
    void init() {
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    }

    void settings() {
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    }

    void initFreeType() {
        FT_Library ft;
        if (FT_Init_FreeType(&ft))
            throw std::runtime_error("ERROR::FREETYPE: Could not init FreeType Library");

        FT_Face face;
        if (FT_New_Face(ft, "../../../engine/fonts/Inter-VariableFont_slnt,wght.ttf", 0, &face))
            throw std::runtime_error("ERROR::FREETYPE: Failed to load font");
        FT_Set_Pixel_Sizes(face, 0, 48);
        if (FT_Load_Char(face, 'X', FT_LOAD_RENDER))
            throw std::runtime_error("ERROR::FREETYTPE: Failed to load Glyph");

        glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // disable byte-alignment restriction
        struct Character {
            unsigned int TextureID;  // ID handle of the glyph texture
            glm::ivec2   Size;       // Size of glyph
            glm::ivec2   Bearing;    // Offset from baseline to left/top of glyph
            FT_Pos Advance;    // Offset to advance to next glyph
        };

        std::map<char, Character> Characters;

        for (unsigned char c = 0; c < 128; c++)
        {
            // load character glyph
            if (FT_Load_Char(face, c, FT_LOAD_RENDER))
            {
                std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
                continue;
            }
            // generate texture
            unsigned int texture;
            glGenTextures(1, &texture);
            glBindTexture(GL_TEXTURE_2D, texture);
            glTexImage2D(
                GL_TEXTURE_2D,
                0,
                GL_RED,
                face->glyph->bitmap.width,
                face->glyph->bitmap.rows,
                0,
                GL_RED,
                GL_UNSIGNED_BYTE,
                face->glyph->bitmap.buffer
            );
            // set texture options
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            // now store character for later use
            Character character = {
                texture,
                glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
                glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
                face->glyph->advance.x
            };
            Characters.insert(std::pair<char, Character>(c, character));
        }
        FT_Done_Face(face);
        FT_Done_FreeType(ft);
    }
}
