include(CMakeDependentOption)

add_library(nightside)
add_library(nightside::game ALIAS nightside)

if (NOT DEFINED NIGHTSIDE_ROOT_DIR)
  message(FATAL_ERROR "NIGHTSIDE_ROOT_DIR has not been specified! Did you some how call the game cmake only?")
endif ()

include(${NIGHTSIDE_ROOT_DIR}/cmake/func/AddTargetSource.cmake)

target_link_libraries(nightside
        PUBLIC

        SFML::Graphics
        SFML::Window

        PRIVATE
        nightside::deps
)

# Setup our include structure
target_include_directories(nightside
        PUBLIC include "${CMAKE_CURRENT_BINARY_DIR}/include"
        PRIVATE "src"
)

add_subdirectory(include/nightside)
add_subdirectory(src)

if ("${CMAKE_CXX_COMPILER_ID}" MATCHES "GNU|Clang|IntelLLVM|AppleClang")
  if ("${CMAKE_CXX_COMPILER_FRONTEND_VARIANT}" STREQUAL "MSVC") # clang-cl
    add_compile_options(nightside INTERFACE /W4056 /W4146 /W4018 /W4056)
  endif ()
  add_compile_options(nightside INTERFACE -Wno-sign-conversion -Wno-format-security)
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
  add_compile_options(nightside INTERFACE /W4056 /W4146 /W4018 /W4056)
endif ()

