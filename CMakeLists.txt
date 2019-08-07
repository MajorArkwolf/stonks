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
    src/AABBList.cpp
    src/PlainNode.cpp
    src/CameraMap.cpp
    src/AABB.cpp
    src/AABBNode.cpp
    src/PlainLinkedList.cpp
    src/Camera.cpp
    src/Collision.cpp
    src/TexturedPolygons.cpp
    src/Workaround.cpp
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
    -Wno-c++98-compat-pedantic -Wno-padded -Wno-deprecated-declarations
    -fcolor-diagnostics>)
target_compile_options(shays-world PUBLIC
    $<$<AND:$<CONFIG:Debug>,$<CXX_COMPILER_ID:Clang>>:-fsanitize=address,undefined,leak>)
target_link_libraries(shays-world PUBLIC
    $<$<AND:$<CONFIG:Debug>,$<CXX_COMPILER_ID:Clang>>:-fsanitize=address,undefined,leak>)

# GCC
target_compile_options(shays-world PUBLIC $<$<CXX_COMPILER_ID:Gnu>:-Wall
    -Wextra -Wpedantic -fdiagnostics-color=always>)

# MSVC
target_compile_options(shays-world PUBLIC $<$<CXX_COMPILER_ID:MSVC>:/W4>)

# Include header files.
target_include_directories(shays-world PRIVATE src)

# Find, include, and link against dependencies.
find_package(OpenGL REQUIRED COMPONENTS OpenGL)
find_package(GLUT REQUIRED)
find_package(glm REQUIRED)

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

# Set dependencies.
add_dependencies(shays-world OpenGL::GL GLUT::GLUT)
# Set includes.
target_include_directories(shays-world PRIVATE ${OPENGL_INCLUDE_DIRS}
    ${GLUT_INCLUDE_DIRS} ${GLM_INCLUDE_DIRS})
# Set link libraries.
target_link_libraries(shays-world PRIVATE OpenGL::GL GLUT::GLUT)

# Copy the resources to the binary location.
add_custom_command(TARGET shays-world POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${CMAKE_SOURCE_DIR}/res
                       $<TARGET_FILE_DIR:shays-world>/res)
