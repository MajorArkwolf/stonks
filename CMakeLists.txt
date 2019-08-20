# Set cmake minimum version.
cmake_minimum_required(VERSION 3.12)

# Set the project details.
set(PROJECT_NAME shays-world)
project(${PROJECT_NAME} LANGUAGES CXX)

# If enabled, the post build symlink will copy instead.
option(CopyResources "CopyResources" OFF)

# Disable in-source builds.
set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)
set(CMAKE_DISABLE_SOURCE_CHANGES ON)

# Set the cmake module paths.
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/sdl2)

# Set build type to debug by default.
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

# Define source files.
set (SOURCES
    src/Main.cpp

    src/Stonk/Engine.cpp
    src/Stonk/Collision.cpp
    src/Stonk/Physics.cpp
    src/Stonk/Viewport.cpp

    src/Shay/AABBList.cpp
    src/Shay/PlainNode.cpp
    src/Shay/CameraMap.cpp
    src/Shay/AABB.cpp
    src/Shay/AABBNode.cpp
    src/Shay/PlainLinkedList.cpp
    src/Shay/Camera.cpp
    src/Shay/Collision.cpp
    src/Shay/TexturedPolygons.cpp
    src/Shay/Shay.cpp
)

# Define the executable.
add_executable(${PROJECT_NAME} ${SOURCES})

# Set C++ standard.
set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
)

# Remove the default warning level from MSVC.
if (MSVC)
    string(REGEX REPLACE "/W[0-4]" "" CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS})
endif()

# Set Clang compile flags.
target_compile_options(${PROJECT_NAME} PUBLIC
    $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>>:
    -Weverything -fcolor-diagnostics
    # These warnings are not useful.
    -Wno-c++98-compat -Wno-c++98-compat-pedantic -Wno-padded
    -Wno-deprecated-declarations -Wno-exit-time-destructors -Wno-switch-enum>)
# Set GCC compile flags.
target_compile_options(${PROJECT_NAME} PUBLIC $<$<CXX_COMPILER_ID:GNU>:
    -Wall -Wextra -Wpedantic -fdiagnostics-color=always>)
# Set MSVC compile flags.
target_compile_options(${PROJECT_NAME} PUBLIC $<$<CXX_COMPILER_ID:MSVC>:/W4>)
target_link_options(${PROJECT_NAME} BEFORE PUBLIC 
    $<$<AND:$<CONFIG:Debug>,$<CXX_COMPILER_ID:MSVC>>:/NODEFAULTLIB:msvcrt.lib>)

# Enable Clang's address and memory sanitizers.
target_compile_options(${PROJECT_NAME} PUBLIC
    $<$<AND:$<CONFIG:Debug>,$<CXX_COMPILER_ID:Clang>>:-fsanitize=address,undefined,leak>)
target_link_options(${PROJECT_NAME} PUBLIC
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
    SDL2::SDL2 SDL2::Image SDL2::TTF SDL2::Mixer glm)

# Symlink or copy the resources to the binary location.
if (NOT CopyResources)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E create_symlink
        ${CMAKE_SOURCE_DIR}/res $<TARGET_FILE_DIR:${PROJECT_NAME}>/res)
else()
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/res $<TARGET_FILE_DIR:${PROJECT_NAME}>/res)
endif()
