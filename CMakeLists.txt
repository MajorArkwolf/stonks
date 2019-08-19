# Set cmake minimum version.
cmake_minimum_required(VERSION 3.12)

# Set the project details.
set(PROJECT_NAME shays-world)
set(PROJECT_VERSION_MAJOR 0)
set(PROJECT_VERSION_MINOR 1)
set(PROJECT_VERSION_PATCH 0)
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

# Set the icon path.
if (APPLE)
    set(ICON_PATH ${CMAKE_SOURCE_DIR}/cmake/macOS/stonk.icns)
    set_source_files_properties(${ICON_PATH} PROPERTIES MACOSX_PACKAGE_LOCATION "Resources")
    list(APPEND SOURCES ${ICON_PATH})
endif()

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
    -Weverything -Wno-c++98-compat -Wno-c++98-compat-pedantic -Wno-padded
    -Wno-deprecated-declarations -fcolor-diagnostics>)
# Set GCC compile flags.
target_compile_options(${PROJECT_NAME} PUBLIC $<$<CXX_COMPILER_ID:GNU>:-Wall
    -Wextra -Wpedantic -fdiagnostics-color=always>)
# Set MSVC compile flags.
target_compile_options(${PROJECT_NAME} PUBLIC $<$<CXX_COMPILER_ID:MSVC>:/W4>)

# Enable Clang's address and memory sanitizers.
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
    SDL2::SDL2 SDL2::Image SDL2::TTF SDL2::Mixer glm)

# Symlink the resources to the binary location.
if (NOT CopyResources)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E create_symlink
        ${CMAKE_SOURCE_DIR}/res $<TARGET_FILE_DIR:${PROJECT_NAME}>/res)
else()
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/res $<TARGET_FILE_DIR:${PROJECT_NAME}>/res)
endif()

# Define install.
if (NOT APPLE)
    install(TARGETS ${PROJECT_NAME} DESTINATION ${PROJECT_NAME})

    install(FILES "${CMAKE_SOURCE_DIR}/LICENSE.md" DESTINATION ${PROJECT_NAME})
    install(FILES "${CMAKE_SOURCE_DIR}/README.md" DESTINATION ${PROJECT_NAME})
    install(DIRECTORY "${CMAKE_SOURCE_DIR}/res" DESTINATION ${PROJECT_NAME})

    set(CPACK_GENERATOR "TGZ")
else()
    # Include the Info.plist.
    set_target_properties(${PROJECT_NAME} PROPERTIES
        MACOSX_BUNDLE TRUE
        MACOSX_BUNDLE_INFO_PLIST ${CMAKE_SOURCE_DIR}/cmake/macOS/Info.plist)

    install(TARGETS ${PROJECT_NAME}
        BUNDLE DESTINATION . COMPONENT Runtime
        RUNTIME DESTINATION bin COMPONENT Runtime)

    install(FILES "${CMAKE_SOURCE_DIR}/LICENSE.md" DESTINATION .)
    install(FILES "${CMAKE_SOURCE_DIR}/README.md" DESTINATION .)

    # Define the app.
    set(APPS "\${CMAKE_INSTALL_PREFIX}/${PROJECT_NAME}.app")
    set(DIRS ${CMAKE_BINARY_DIR})
    install(CODE "include(BundleUtilities)
        fixup_bundle(\"${APPS}\" \"\" \"${DIRS}\")")
    set(CPACK_GENERATOR "DragNDrop")
endif()

# Copy libraries to the binary directory.
if(NOT APPLE)
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    $<TARGET_FILE:SDL2::Core>
    $<TARGET_FILE:SDL2::Image>
    $<TARGET_FILE:SDL2::TTF>
    $<TARGET_FILE:SDL2::Mixer>
    $<TARGET_FILE_DIR:${PROJECT_NAME}>)
else()
    # The above code doesn't resolve symlinks for whatever reason.
    get_filename_component(SDL2_CORE_PATH ${SDL2_LIBRARIES} REALPATH)
    get_filename_component(SDL2_IMAGE_PATH ${SDL2_IMAGE_LIBRARIES} REALPATH)
    get_filename_component(SDL2_TTF_PATH ${SDL2_TTF_LIBRARIES} REALPATH)
    get_filename_component(SDL2_MIXER_PATH ${SDL2_MIXER_LIBRARIES} REALPATH)

    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${SDL2_CORE_PATH}
        ${SDL2_IMAGE_PATH}
        ${SDL2_TTF_PATH}
        ${SDL2_MIXER_PATH}
        $<TARGET_FILE_DIR:${PROJECT_NAME}>)
endif()

# Cpack settings.
set(CPACK_PACKAGE_VENDOR "Stonk")
set(CPACK_PACKAGE_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${PROJECT_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${PROJECT_VERSION_PATCH})
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_SOURCE_DIR}/LICENSE.md")
set(CPACK_RESOURCE_FILE_README "${CMAKE_SOURCE_DIR}/README.md")
set(CPACK_SOURCE_IGNORE_FILES .DS_Store)

if (APPLE)
    set(CPACK_PACKAGE_FILE_NAME "$ENV{TRAVIS_TAG}-osx")
elseif (UNIX)
    set(CPACK_PACKAGE_FILE_NAME "$ENV{TRAVIS_TAG}-linux")
elseif (WIN32)
    set(CPACK_PACKAGE_FILE_NAME "$ENV{TRAVIS_TAG}-windows")
endif()

include(CPack)
