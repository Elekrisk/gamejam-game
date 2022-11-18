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

add_custom_target(run
    COMMAND game
    DEPENDS game
    WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
)
