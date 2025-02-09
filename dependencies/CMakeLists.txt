project(nightside-dependencies)

include(FetchContent)
set(BUILD_SHARED_LIBS OFF)

# SFML
FetchContent_Declare(sfml
        GIT_REPOSITORY https://github.com/SFML/SFML
        GIT_TAG 3.0.0
)
FetchContent_MakeAvailable(sfml)

# Dear ImGui
add_subdirectory(imgui)

# Dear ImGui-SFML
set(IMGUI_SFML_FIND_SFML OFF)
add_subdirectory(imgui-sfml)

# djson
FetchContent_Declare(
        djson
        GIT_REPOSITORY https://github.com/karnkaul/djson
        GIT_TAG v2.1.1
)
FetchContent_MakeAvailable(djson)

# Avoid warning about DOWNLOAD_EXTRACT_TIMESTAMP in CMake 3.24 with steamworks.
if (CMAKE_VERSION VERSION_GREATER_EQUAL "3.24.0")
    cmake_policy(SET CMP0135 NEW)
endif ()

add_library(nightside-dependencies INTERFACE)
add_library(nightside::deps ALIAS nightside-dependencies)

target_link_libraries(nightside-dependencies INTERFACE
        djson::djson
        ImGui-SFML::ImGui-SFML
        SFML::System
        SFML::Graphics
        SFML::Window
        SFML::Audio
)

if ("${CMAKE_CXX_COMPILER_ID}" MATCHES "GNU|Clang|IntelLLVM|AppleClang")
  if ("${CMAKE_CXX_COMPILER_FRONTEND_VARIANT}" STREQUAL "MSVC") # clang-cl
    add_compile_options(nightside-dependencies INTERFACE /W0)
  endif ()
  add_compile_options(nightside-dependencies INTERFACE -w)
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
  add_compile_options(nightside-dependencies INTERFACE /W0)
endif ()
