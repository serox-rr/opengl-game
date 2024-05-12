module;
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <initializer_list>
#include <map>
#include <optional>
#include <string>
#include "glm/fwd.hpp"
#include <span>
export module engine:shader;

export namespace Engine {
    const std::map<const unsigned, std::string> shaderType({{GL_VERTEX_SHADER, "VERTEX"},
                                                      {GL_FRAGMENT_SHADER, "FRAGMENT"},
                                                      {GL_GEOMETRY_SHADER, "GEOMETRY"},
                                                      {GL_TESS_CONTROL_SHADER, "TESSELATION_CONTROL"},
                                                      {GL_TESS_EVALUATION_SHADER, "TESSELATION_EVALUATION"}});
    class Shader {
    public:
        Shader(const std::initializer_list<std::string> &uniformsName, const std::string &vertexPath,
               const std::string &fragmentPath, const std::optional<std::string> &geometryPath,
               const std::optional<std::string> &tessellationControlPath,
               const std::optional<std::string> &tessellationEvaluationPath);

        void use() const;

        void setBool(std::string_view name, bool value) const;

        void setInt(std::string_view name, int value) const;

        void setFloat(std::string_view name, float value) const;

        void setMat4(std::string_view name, const glm::mat4 &matrix) const;

        void setMat3(std::string_view name, const glm::mat3 &matrix) const;

        void setVec3(std::string_view name, const glm::vec3 &vec3) const;

        void addUniform(const std::string &name);

        void addUniforms(const std::initializer_list<std::string> &names);

        [[nodiscard]] unsigned getId() const;

    private:
        unsigned int id;
        std::map<const std::string, unsigned, std::less<>> uniforms;
        static void checkCompileErrors(unsigned int shader, std::string_view type);
        void addShaderFile(std::string_view path, unsigned type) const;
    };
} // namespace Engine
