module;
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <initializer_list>
#include <iostream>
#include <optional>
#include <string>

module engine;
namespace Engine {
    Shader::Shader(const std::initializer_list<std::string> &uniformsName, const std::string &vertexPath,
                   const std::string &fragmentPath, const std::optional<std::string> &geometryPath,
                   const std::optional<std::string> &tessellationControlPath,
                   const std::optional<std::string> &tessellationEvaluationPath) : id(glCreateProgram()), uniforms({}) {
        addShaderFile(vertexPath, GL_VERTEX_SHADER);
        addShaderFile(fragmentPath, GL_FRAGMENT_SHADER);
        if (geometryPath.has_value()) {
            addShaderFile(geometryPath.value(), GL_GEOMETRY_SHADER);
        }
        if (tessellationControlPath.has_value()) {
            addShaderFile(tessellationControlPath.value(), GL_TESS_CONTROL_SHADER);
        }
        if (tessellationEvaluationPath.has_value()) {
            addShaderFile(tessellationEvaluationPath.value(), GL_TESS_EVALUATION_SHADER);
        }
        glLinkProgram(id);
        checkCompileErrors(id, "PROGRAM");
        for (auto name: uniformsName) {
            uniforms.insert({name, glGetUniformLocation(id, name.c_str())});
        }
    }

    void Shader::use() const { glUseProgram(id); }

    void Shader::setBool(const std::string_view name, const bool value) const {
        if (const auto it = uniforms.find(name); it != uniforms.end())
            glUniform1i(it->second, static_cast<int>(value));
    }

    void Shader::setInt(const std::string_view name, const int value) const {
        if (const auto it = uniforms.find(name); it != uniforms.end())
            glUniform1i(it->second, value);
    }

    void Shader::setFloat(const std::string_view name, const float value) const {
        if (const auto it = uniforms.find(name); it != uniforms.end())
            glUniform1f(it->second, value);
    }

    void Shader::setVec3(const std::string_view name, const glm::vec3 &vec3) const {
        if (const auto it = uniforms.find(name); it != uniforms.end())
            glUniform3f(it->second, vec3.x, vec3.y, vec3.z);
    }

    void Shader::setMat4(const std::string_view name, const glm::mat4 &matrix) const {
        if (const auto it = uniforms.find(name); it != uniforms.end())
            glUniformMatrix4fv(it->second, 1, GL_FALSE, glm::value_ptr(matrix));
    }

    void Shader::setMat3(const std::string_view name, const glm::mat3 &matrix) const {
        if (const auto it = uniforms.find(name); it != uniforms.end())
            glUniformMatrix3fv(it->second, 1, GL_FALSE, glm::value_ptr(matrix));
    }

    void Shader::addUniform(const std::string &name) {
        if (!uniforms.contains(name))
            uniforms.insert({name, glGetUniformLocation(id, name.c_str())});
    }

    void Shader::addUniforms(const std::initializer_list<std::string> &names) {
        for (const auto &name: names) {
            addUniform(name);
        }
    }

    void Shader::addShaderFile(const std::string_view path, const unsigned type) const {
        std::string a = getFile(path);
        const char *s = a.c_str();
        const unsigned shader(glCreateShader(type));
        glShaderSource(shader, 1, &s, nullptr);
        glCompileShader(shader);
        checkCompileErrors(shader, shaderType.at(type));
        glAttachShader(id, shader);
        glDeleteShader(shader);
    }

    void Shader::checkCompileErrors(const unsigned int shader, const std::string_view type) {
        int success;
        char infoLog[1024];
        if (type != "PROGRAM") {
            glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
            if (!success) {
                glGetShaderInfoLog(shader, 1024, nullptr, infoLog);
                std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n"
                          << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
            }
            return;
        }
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(shader, 1024, nullptr, infoLog);
            std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n"
                      << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }

    unsigned Shader::getId() const { return id; }

} // namespace Engine
