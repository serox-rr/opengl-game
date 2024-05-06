module;
#include <fstream>
#include <iostream>
#include <sstream>
#include <string_view>
module engine;

namespace Engine {
    std::string getFile(const std::string_view path) {
        try {
            std::ifstream file;
            file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
            std::stringstream stream;
            file.open(path.data());
            stream << file.rdbuf();
            file.close();
            return stream.str();
        }
        catch (std::ifstream::failure &e) {
            std::cout << "FAILED TO READ FILE: " << e.what() << std::endl;
        }
        return "";
    }
} // namespace Engine
