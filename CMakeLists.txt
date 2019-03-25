cmake_minimum_required(VERSION 3.12)
project(SpaceInvaders)

set(CMAKE_CXX_STANDARD 11)

find_package(SDL2 CONFIG REQUIRED)
add_subdirectory(GameEngine)
# Load tools from game engine
add_subdirectory(GameEngine/tools)

set(GAME_SOURCES
        main.cpp
        EnemyComponent.cpp
        EnemyManagerComponent.cpp
        PlayerComponent.cpp
        BulletComponent.cpp
        HUDComponent.cpp
        StartMenuComponent.cpp
        MotherShipComponent.cpp
        BlinkTextComponent.cpp
        EnemyExplosionComponent.cpp
        GameManagerComponent.cpp
        ShelterComponent.cpp)

# auto-generated files
file(GLOB COMPONENTS_REGISTERED_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/*.hpp")
generate_components_register("componentsRegistered" FILE_GENERATED
        COMPONENTS ${COMPONENTS_REGISTERED_HEADERS})

add_executable(SpaceInvaders ${ENGINE_SOURCES} ${GAME_SOURCES} ${FILE_GENERATED})
configure_game_directories(SpaceInvaders data conf assets)

target_link_libraries(SpaceInvaders PRIVATE
        SDL2::SDL2main
        GameEngine)