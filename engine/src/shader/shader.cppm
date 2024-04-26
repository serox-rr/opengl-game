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

        void setBool(const char* name, bool value) const;

        void setInt(const char* name, int value) const;

        void setFloat(const char* name, float value) const;

        void setMat4(const char* name, glm::mat4* matrix) const;

    private:
        static void checkCompileErrors(unsigned int shader, const std::string&type);

        std::map<const char *, int> uniforms;
    };
}
