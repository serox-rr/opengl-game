module;
#include <exception>
#include <map>
#include <stdexcept>
#include <unordered_map>

export module engine:exception;

namespace Engine {
    enum class FreetypeErrorCodes {
        LIBRARY_LOADING,
        FONT_LOADING,
        GLYPH_LOADING
    };
    class FreetypeError final: public std::exception {
    public:
        explicit FreetypeError(FreetypeErrorCodes _code) noexcept;
        [[nodiscard]] const char* what() const noexcept override;
        [[nodiscard]] FreetypeErrorCodes getCode() const;
    private:
        const std::unordered_map<FreetypeErrorCodes, std::string> description;
        const FreetypeErrorCodes code;
    };
}
