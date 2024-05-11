module;
#include <string>
export module engine:texture;
export namespace Engine {
    class Texture {
    public:
        Texture(const char *texturePath, unsigned int textureUnit, const char *imageType);
        [[nodiscard]] unsigned get() const;

    private:
        unsigned ID;
    };

    unsigned int TextureFromFile(const char *path, const std::string &directory, bool gamma);
} // namespace Engine
