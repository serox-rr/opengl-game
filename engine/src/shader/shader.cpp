module;
#include <fstream>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <initializer_list>
#include <iostream>
#include <ranges>
#include <sstream>
#include <string>
module engine;

namespace Engine {
    Shader::Shader(const std::string &vertexPath, const std::string &fragmentPath,
                   std::initializer_list<std::string> uniformsName) : ID(0), uniforms({}) {
        std::string vertexCode;
        std::string fragmentCode;
        std::ifstream vShaderFile;
        std::ifstream fShaderFile;
        // ensure ifstream objects can throw exceptions:
        vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        try {
            // open files
            vShaderFile.open(vertexPath);
            fShaderFile.open(fragmentPath);
            std::stringstream vShaderStream, fShaderStream;
            // read file's buffer contents into streams
            vShaderStream << vShaderFile.rdbuf();
            fShaderStream << fShaderFile.rdbuf();
            // close file handlers
            vShaderFile.close();
            fShaderFile.close();
            // convert stream into string
            vertexCode = vShaderStream.str();
            fragmentCode = fShaderStream.str();
        }
        catch (std::ifstream::failure &e) {
            std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ: " << e.what() << std::endl;
        }
        const char *vShaderCode = vertexCode.c_str();
        const char *fShaderCode = fragmentCode.c_str();
        // 2. compile shaders
        unsigned vertex(glCreateShader(GL_VERTEX_SHADER));
        // vertex shader
        glShaderSource(vertex, 1, &vShaderCode, NULL);
        glCompileShader(vertex);
        checkCompileErrors(vertex, "VERTEX");
        // fragment Shader
        unsigned fragment(glCreateShader(GL_FRAGMENT_SHADER));
        glShaderSource(fragment, 1, &fShaderCode, NULL);
        glCompileShader(fragment);
        checkCompileErrors(fragment, "FRAGMENT");
        // shader Program
        ID = glCreateProgram();
        glAttachShader(ID, vertex);
        glAttachShader(ID, fragment);
        glLinkProgram(ID);
        checkCompileErrors(ID, "PROGRAM");
        // delete the shaders as they're linked into our program now and no longer necessary
        glDeleteShader(vertex);
        glDeleteShader(fragment);

        for (auto name: uniformsName) {
            uniforms.insert({name, glGetUniformLocation(ID, name.c_str())});
        }
    }

    void Shader::use() const { glUseProgram(ID); }

    void Shader::setBool(const std::string &name, const bool value) const {
        glUniform1i(uniforms.at(name), static_cast<int>(value));
    }

    void Shader::setInt(const std::string &name, const int value) const { glUniform1i(uniforms.at(name), value); }

    void Shader::setFloat(const std::string &name, const float value) const { glUniform1f(uniforms.at(name), value); }

    void Shader::setVec3(const std::string &name, const glm::vec3 &vec3) const {
        glUniform3f(uniforms.at(name), vec3.x, vec3.y, vec3.y);
    }


    void Shader::checkCompileErrors(const unsigned int shader, const std::string &type) {
        int success;
        char infoLog[1024];
        if (type != "PROGRAM") {
            glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
            if (!success) {
                glGetShaderInfoLog(shader, 1024, NULL, infoLog);
                std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n"
                          << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
            }
        }
        else {
            glGetProgramiv(shader, GL_LINK_STATUS, &success);
            if (!success) {
                glGetProgramInfoLog(shader, 1024, NULL, infoLog);
                std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n"
                          << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
            }
        }
    }

    void Shader::setMat4(const std::string &name, const glm::mat4 &matrix) const {
        glUniformMatrix4fv(uniforms.at(name), 1, GL_FALSE, glm::value_ptr(matrix));
    }

    unsigned Shader::getId() const { return ID; }

} // namespace Engine
