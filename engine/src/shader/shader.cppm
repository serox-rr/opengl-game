module;
#include "glm/fwd.hpp"
#include <string>
#include <vector>
#include <map>
export module engine:shader;

export namespace Engine {
    class Shader {
    public:
        unsigned int ID;

        Shader(const char* vertexPath, const char* fragmentPath, std::vector<const char *> uniformsName);

        void use() const;

        void setBool(const std::string&name, const bool value) const;

        void setInt(const std::string&name, const int value) const;

        void setFloat(const std::string name, const float value) const;

        void setMat4(const std::string &name, glm::mat4 &matrix) const;

    private:
        static void checkCompileErrors(const unsigned int shader, const std::string&type);

        std::map<std::string, int> uniforms;
    };
}
