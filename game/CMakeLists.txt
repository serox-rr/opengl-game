cmake_minimum_required(VERSION 3.28)
project(game VERSION 0.0.1)

set(game-SRC
        game.cpp
        game.h
)

add_executable (game ${game-SRC})

set_property(TARGET game PROPERTY CXX_STANDARD 23)

target_link_libraries(game PUBLIC engine)
