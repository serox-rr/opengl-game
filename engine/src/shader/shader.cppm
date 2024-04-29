module;
#include <map>
#include <string>
#include <initializer_list>
#include "glm/fwd.hpp"
export module engine:shader;

export namespace Engine {
    class Shader {
    public:
        Shader(const std::string &vertexPath, const std::string &fragmentPath, std::initializer_list<std::string> uniformsName);

        void use() const;

        void setBool(const std::string &name, bool value) const;

        void setInt(const std::string &name, int value) const;

        void setFloat(const std::string &name, float value) const;

        void setMat4(const std::string &name, glm::mat4 &matrix) const;

        void setVec3(const std::string &name, const glm::vec3 &vec3) const;

        [[nodiscard]] unsigned getId() const;

    private:
        unsigned int ID;
        static void checkCompileErrors(unsigned int shader, const std::string &type);
        std::map<const std::string, unsigned> uniforms;
    };
} // namespace Engine
