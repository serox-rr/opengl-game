module;
#include <string_view>
export module engine:utils;

export namespace Engine {
    std::string getFile(std::string_view path);
}
