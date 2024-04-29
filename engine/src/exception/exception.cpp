module;

module engine;

namespace Engine {
    FreetypeError::FreetypeError(const FreetypeErrorCodes _code) noexcept: description({
                                                                               {
                                                                                   FreetypeErrorCodes::FONT_LOADING,
                                                                                   "Could not init FreeType Library"
                                                                               },
                                                                               {
                                                                                   FreetypeErrorCodes::LIBRARY_LOADING,
                                                                                   "Failed to load font"
                                                                               },
                                                                               {
                                                                                   FreetypeErrorCodes::GLYPH_LOADING,
                                                                                   "Failed to load Glyph"
                                                                               }
                                                                           }), code(_code) {
    }

    const char* FreetypeError::what() const noexcept {
        return description.at(code).c_str();
    }

    FreetypeErrorCodes FreetypeError::getCode() const {
        return code;
    }
}
