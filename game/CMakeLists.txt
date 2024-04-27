cmake_minimum_required(VERSION 3.28)
project(game VERSION 0.0.1)


file(GLOB_RECURSE MDLS *.cppm)
file(GLOB_RECURSE SRCS *.cpp)

add_executable (game)
target_sources(game PUBLIC ${SRCS})
target_sources(game PUBLIC FILE_SET CXX_MODULES FILES ${MDLS})

set_property(TARGET game PROPERTY CXX_STANDARD 23)

target_link_libraries(game PUBLIC engine)
