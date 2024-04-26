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

# Fetch GLFW
FetchContent_Declare(
  glfw
  GIT_REPOSITORY https://github.com/glfw/glfw.git
  GIT_TAG        3.4 # Replace with the desired version
)
FetchContent_MakeAvailable(glfw)

# Fetch GLAD
FetchContent_Declare(
  glad
  GIT_REPOSITORY https://github.com/Dav1dde/glad.git
  GIT_TAG        master # You can specify a branch, tag, or commit hash
)
FetchContent_MakeAvailable(glad)

if(NOT glad_POPULATED)
    FetchContent_Populate(glad)
    set(GLAD_PROFILE "core" CACHE STRING "OpenGL profile")
    set(GLAD_API "gl=" CACHE STRING "API type/version pairs, like \"gl=3.2,gles=\", no version means latest")
    set(GLAD_GENERATOR "c" CACHE STRING "Language to generate the binding for")
    add_subdirectory(${glad_SOURCE_DIR} ${glad_BINARY_DIR})
endif()

# Fetch GLM
FetchContent_Declare(
  glm
  GIT_REPOSITORY https://github.com/g-truc/glm.git
  GIT_TAG        1.0.1 # Replace with the desired version
)
FetchContent_MakeAvailable(glm)

FetchContent_Declare(
    stb
    GIT_REPOSITORY https://github.com/nothings/stb.git
    GIT_TAG        master
)

FetchContent_MakeAvailable(stb)
# Include the directory containing stb headers
target_include_directories(engine PUBLIC ${stb_SOURCE_DIR} )

FetchContent_Declare(
    fastnoise
    GIT_REPOSITORY https://github.com/Auburn/FastNoise2.git
    GIT_TAG        v0.10.0-alpha
)

FetchContent_MakeAvailable(fastnoise)


# Now you can use these libraries in your project

target_link_libraries(engine PUBLIC glfw glad glm)
