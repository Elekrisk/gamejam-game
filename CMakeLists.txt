cmake_minimum_required(VERSION 3.22)

project(gamejam-game)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_BUILD_TYPE Debug)

add_executable(game
    src/main.cpp
    src/entity.hpp
    src/entity.cpp
    src/item.hpp
    src/player.hpp
    src/player.cpp
    src/renderer.hpp
    src/renderer.cpp
    src/world.hpp
    src/world.cpp
    src/sprite.hpp
    src/sprite.cpp
)

target_link_libraries(game sfml-graphics sfml-window sfml-system)

# Copies assets into build directory
add_custom_command(
    TARGET game PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/assets/ $<TARGET_FILE_DIR:game>/assets/
)

add_custom_target(run
    COMMAND game
    DEPENDS game
    WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
)