cmake_minimum_required(VERSION 3.22)

project(gamejam-game)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_COLOR_DIAGNOSTICS true)

add_executable(game
    src/main.cpp
    src/entity.hpp
    src/entity.cpp
    src/item.hpp
    src/item.cpp
    src/player.hpp
    src/player.cpp
    src/renderer.hpp
    src/renderer.cpp
    src/world.hpp
    src/world.cpp
    src/sprite.hpp
    src/sprite.cpp
    src/asset_manager.hpp
    src/asset_manager.cpp
    src/wall.hpp
    src/wall.cpp
    src/item_entity.hpp
    src/item_entity.cpp
    src/geiger.cpp
    src/geiger.hpp
    src/mimic.hpp
    src/mimic.cpp
    src/level_parser.hpp
    src/level_parser.cpp
    src/key.cpp
    src/key.cpp
    src/renderview.hpp
    src/renderview.cpp
    src/render_constants.hpp
    src/chest.hpp
    src/chest.cpp
    src/camera.hpp
    src/camera.cpp
    src/treasure.hpp
    src/treasure.cpp
    src/lever.hpp
    src/lever.cpp
    src/gate.hpp
    src/gate.cpp
    src/goal.hpp
    src/goal.cpp
    src/state_stack.hpp
    src/state_stack.cpp
    src/level_button.hpp
    src/level_button.cpp
)

target_link_libraries(game sfml-graphics sfml-window sfml-system sfml-audio)

# Copies assets into build directory
add_custom_command(
    TARGET game POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/assets/ $<TARGET_FILE_DIR:game>/assets/
)

add_custom_target(run
    COMMAND game
    DEPENDS game
    WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
)

add_custom_target(copy_assets
    COMMAND cp -r ${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:game>
)