
cmake_minimum_required(VERSION 3.15)

set(CMAKE_CXX_STANDARD 20)

if (NOT DEFINED NIGHTSIDE_ROOT_DIR)
  set(NIGHTSIDE_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR} CACHE STRING "Nightside root directory")
endif ()

project(nightside
        LANGUAGES CXX
        VERSION 1.0
)

include(cmake/func/AddTargetSource.cmake)
include(cmake/GenerateDataTemplates.cmake)

add_subdirectory(dependencies)
add_subdirectory(launcher)
add_subdirectory(game)

