# Set cmake minimum version.
cmake_minimum_required(VERSION 3.13)

# Set the project details.
set(PROJECT_NAME shays-world)
project(${PROJECT_NAME} LANGUAGES CXX)

# Disable in-source builds.
set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)
set(CMAKE_DISABLE_SOURCE_CHANGES ON)

# Set the cmake module paths.
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/sdl2)

# Set build type to debug by default.
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

# Define executable source files.
add_executable(${PROJECT_NAME}
    src/Main.cpp
    src/AABBList.cpp
    src/PlainNode.cpp
    src/CameraMap.cpp
    src/AABB.cpp
    src/AABBNode.cpp
    src/PlainLinkedList.cpp
    src/Camera.cpp
    src/Collision.cpp
    src/TexturedPolygons.cpp

	src/Shay.cpp

    src/Stonk/Collision.cpp
    src/Stonk/Physics.cpp
    src/Stonk/Stonk.cpp
    src/Stonk/Viewport.cpp
)

# Set C++ standard.
set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
)

# Set clang compile flags.
target_compile_options(${PROJECT_NAME} PUBLIC
    $<$<CXX_COMPILER_ID:Clang>:-Weverything -Wno-c++98-compat
    -Wno-c++98-compat-pedantic -Wno-padded -Wno-deprecated-declarations
    -fcolor-diagnostics>)
# Set gcc compile flags.
target_compile_options(${PROJECT_NAME} PUBLIC $<$<CXX_COMPILER_ID:Gnu>:-Wall
    -Wextra -Wpedantic -fdiagnostics-color=always>)
# Set MSVC compile flags.
target_compile_options(${PROJECT_NAME} PUBLIC $<$<CXX_COMPILER_ID:MSVC>:/W4>)

# Enable clang's address and memory sanitizers.
target_compile_options(${PROJECT_NAME} PUBLIC
    $<$<AND:$<CONFIG:Debug>,$<CXX_COMPILER_ID:Clang>>:-fsanitize=address,undefined,leak>)
target_link_libraries(${PROJECT_NAME} PUBLIC
    $<$<AND:$<CONFIG:Debug>,$<CXX_COMPILER_ID:Clang>>:-fsanitize=address,undefined,leak>)

# Find dependencies.
find_package(OpenGL REQUIRED COMPONENTS OpenGL)
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_mixer REQUIRED)
find_package(glm REQUIRED)

# Include project header files.
target_include_directories(${PROJECT_NAME} PRIVATE src)

# Include and link against dependencies.
target_link_libraries(${PROJECT_NAME} PUBLIC OpenGL::GL OpenGL::GLU
    SDL2::Main SDL2::Image SDL2::TTF SDL2::Mixer glm)

# Symlink the resources to the binary location.
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E create_symlink
                       ${CMAKE_SOURCE_DIR}/res
                       $<TARGET_FILE_DIR:${PROJECT_NAME}>/res)

# Set Visual Studio to build inside the "build" directory, not inside the users
# home directory.
set_target_properties(${PROJECT_NAME} PROPERTIES
    VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/build")
