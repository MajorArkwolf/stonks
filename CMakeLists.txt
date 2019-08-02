# Set cmake minimum version.
cmake_minimum_required(VERSION 3.12)

# Disable in-source builds.
set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)
set(CMAKE_DISABLE_SOURCE_CHANGES ON)

# Detect Linux.
if(UNIX AND NOT APPLE)
    set(LINUX TRUE)
endif()

# Set build type to Debug by default.
if(NOT CMAKE_BUILD_TYPE)
    message(STATUS "Build type not set, defaulting to 'Debug'")
    set(CMAKE_BUILD_TYPE Debug)
else()
    message(STATUS "Build type: '${CMAKE_BUILD_TYPE}'")
endif()

# Define project.
project(shays-world LANGUAGES CXX)

# Define executable source files.
add_executable(shays-world
    src/Main.cpp
    src/AABBLinkedList.cpp
    src/EasySound.cpp
    src/PlainNode.cpp
    src/SoundTime.cpp
    src/CameraMap.cpp
    src/AABB.cpp
    src/AABBNode.cpp
    src/PlainLinkedList.cpp
    src/Sound.cpp
    src/Camera.cpp
    src/Collision.cpp
    src/TexturedPolygons.cpp
)

# Set C++ standard.
set_target_properties(shays-world PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
)

# Set compiler and linker flags.
target_compile_options(shays-world PUBLIC
    $<$<CXX_COMPILER_ID:Clang>:-Weverything -Wno-c++98-compat
    -Wno-c++98-compat-pedantic -Wno-shadow -Wno-padded -Wno-deprecated-declarations
    -fcolor-diagnostics>)
target_compile_options(shays-world PUBLIC
    $<$<AND:$<CONFIG:Debug>,$<CXX_COMPILER_ID:Clang>>:-fsanitize=address,undefined,leak>)
target_link_libraries(shays-world PUBLIC
    $<$<AND:$<CONFIG:Debug>,$<CXX_COMPILER_ID:Clang>>:-fsanitize=address,undefined,leak>)

# GCC
target_compile_options(shays-world PUBLIC $<$<CXX_COMPILER_ID:Gnu>:-Wall
    -Wextra -Wpedantic -fdiagnostics-color=always>)

# MSVC
target_compile_options(shays-world PUBLIC $<$<CXX_COMPILER_ID:MSVC>:/W4 /wd4458>)

# Include header files.
target_include_directories(shays-world PRIVATE src)

# Find, include, and link against dependencies.
find_package(OpenGL REQUIRED COMPONENTS OpenGL)
find_package(GLUT REQUIRED)
find_package(SDL REQUIRED)
add_dependencies(shays-world OpenGL::GL GLUT::GLUT)
target_include_directories(shays-world PRIVATE ${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS}
    ${SDL_INCLUDE_DIR})
target_link_libraries(shays-world PRIVATE OpenGL::GL ${SDL_LIBRARY})

# Hack to fix Linux Glu library paths.
if (LINUX)
    target_link_libraries(shays-world PRIVATE ${OPENGL_glu_LIBRARY})
endif()

# Hack to fix macOS GLUT framework paths.
if (APPLE)
    find_library(APP_SERVICES ApplicationServices)

    set_target_properties(GLUT::GLUT PROPERTIES
        IMPORTED_LOCATION "/System/Library/Frameworks/GLUT.framework/GLUT")
    set_target_properties(GLUT::Cocoa PROPERTIES
        IMPORTED_LOCATION "/System/Library/Frameworks/Cocoa.framework/Cocoa")

    target_link_libraries(shays-world PRIVATE ${APP_SERVICES})
endif()

target_link_libraries(shays-world PRIVATE GLUT::GLUT)

# Custom target to run the project.
add_custom_target(run
  COMMAND shays-world
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
  COMMENT "Running project"
)

add_dependencies(run shays-world)

add_custom_command(TARGET shays-world POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${CMAKE_SOURCE_DIR}/res
                       $<TARGET_FILE_DIR:shays-world>/res)
