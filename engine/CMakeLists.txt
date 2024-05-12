cmake_minimum_required(VERSION 3.28)
project(engine VERSION 0.0.1)

file(COPY
        # you don't want to hardcode the path here in a real-world project,
        # but you get the idea
        "C:/Program Files/Microsoft Visual Studio/2022/Community/VC/Tools/MSVC/14.39.33519/modules/std.ixx"
        DESTINATION
        ${PROJECT_BINARY_DIR}/stdxx
)

file(GLOB_RECURSE MDLS *.cppm)
file(GLOB_RECURSE SRCS *.cpp)

add_library(engine STATIC)

target_sources(engine PUBLIC ${SRCS})
target_sources(engine PUBLIC FILE_SET CXX_MODULES FILES ${MDLS})
#[[target_sources(engine PUBLIC FILE_SET CXX_MODULES
        BASE_DIRS ${PROJECT_BINARY_DIR}/stdxx
        FILES ${PROJECT_BINARY_DIR}/stdxx/std.ixx )]]


set_property(TARGET engine PROPERTY CXX_STANDARD 23)


include(FetchContent)

FetchContent_Declare(
    fastnoise
    GIT_REPOSITORY https://github.com/Auburn/FastNoise2.git
    GIT_TAG        v0.10.0-alpha
)

FetchContent_MakeAvailable(fastnoise)
set(FASTNOISE2_NOISETOOL OFF CACHE BOOL "Build Noise Tool" FORCE)

find_package(Freetype REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(Stb REQUIRED)
find_package(assimp CONFIG REQUIRED)
target_link_libraries(engine PUBLIC glfw glad::glad glm::glm FastNoise Freetype::Freetype assimp::assimp)
target_include_directories(engine PUBLIC ${Stb_INCLUDE_DIR})
