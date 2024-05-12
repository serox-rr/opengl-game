module;
#include <glad/glad.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <stdexcept>
module engine;


namespace Engine {
    Texture::Texture(const char *texturePath, unsigned int textureUnit, const char *imageType) : ID(0) {
        glGenTextures(1, &this->ID);
        glActiveTexture(textureUnit);
        glBindTexture(GL_TEXTURE_2D, this->ID);
        glBindTexture(GL_TEXTURE_2D,
                      this->ID); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
        // set the texture wrapping parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
                        GL_REPEAT); // set texture wrapping to GL_REPEAT (default wrapping method)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        // set texture filtering parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // load image, create texture and generate mipmaps
        int width, height, nrChannels;
        // The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform;
        // replace it with your own image path.
        stbi_set_flip_vertically_on_load(true);
        unsigned char *data = stbi_load(texturePath, &width, &height, &nrChannels, 0);
        if (!data) {
            throw std::runtime_error("Fichier introuvable !");
        }
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, !strcmp(imageType, "jpg") ? GL_RGB : GL_RGBA,
                     GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        stbi_image_free(data);
    }

    unsigned Texture::get() const { return ID; }

    unsigned TextureFromFile(const std::string &filename, const std::string &directory, bool gamma) {
        auto path = directory + '/' + filename;

        unsigned textureID;
        glGenTextures(1, &textureID);

        int width, height, nrComponents;
        unsigned char *data = stbi_load(path.c_str(), &width, &height, &nrComponents, 0);
        if (!data) {
            stbi_image_free(data);
            throw std::runtime_error("Texture failed to load at path: " + std::string(path));
        }
        GLenum format;
        switch (nrComponents) {
            case 1:
                format = GL_RED;
                break;
            case 3:
                format = GL_RGB;
                break;
            case 4:
                format = GL_RGBA;
                break;
            default:
                format = GL_RGB;
        }

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, static_cast<int>(format), width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        stbi_image_free(data);
        return textureID;
    }
} // namespace Engine
