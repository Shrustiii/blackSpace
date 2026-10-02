cmake_minimum_required(VERSION 3.20)
project(BlackSpace VERSION 1.0.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(raylib 5.5 QUIET)
if(NOT raylib_FOUND)
    include(FetchContent)
    set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
    FetchContent_Declare(raylib
        GIT_REPOSITORY https://github.com/raysan5/raylib.git
        GIT_TAG 5.5
        GIT_SHALLOW TRUE
    )
    FetchContent_MakeAvailable(raylib)
endif()

add_executable(blackspace
    main.cpp
    GameController.cpp
    HUD.cpp
    MissionLog.cpp
    Obstacle.cpp
    PlayerShip.cpp
    RescueTarget.cpp
)
target_link_libraries(blackspace PRIVATE raylib)
if(MSVC)
    target_compile_options(blackspace PRIVATE /W4)
else()
    target_compile_options(blackspace PRIVATE -Wall -Wextra -Wpedantic)
endif()
