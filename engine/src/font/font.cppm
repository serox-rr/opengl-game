module;
#include <map>
#include <string>
#include <ft2build.h>
#include FT_FREETYPE_H
#include <glm/glm.hpp>
#include <glm/fwd.hpp>
#include <glm/vec2.hpp>
export module engine:font;
export namespace Engine {
    struct Character;

    class Font {
    public:
        explicit Font(const std::string&_path);

        std::map<char, Character>& getCharacters();

    private:
        std::map<char, Character> characters;
        std::string path;
    };

    struct Character {
        unsigned int textureID; // ID handle of the glyph texture
        glm::ivec2 size; // Size of glyph
        glm::ivec2 bearing; // Offset from baseline to left/top of glyph
        FT_Pos advance; // Offset to advance to next glyph
    };
}
