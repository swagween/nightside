project(nightside-launcher)

if (NOT DEFINED NIGHTSIDE_ROOT_DIR)
  message(FATAL_ERROR "NIGHTSIDE_ROOT_DIR has not been specified! Did you somehow call the launcher cmake only?")
endif ()

add_executable(nightside-launcher)
set_target_properties(nightside-launcher PROPERTIES OUTPUT_NAME "nightside")
target_link_libraries(nightside-launcher PRIVATE
        nightside::deps
        nightside::game
)

target_include_directories(nightside-launcher
        PUBLIC include "${CMAKE_CURRENT_BINARY_DIR}/include"
        PRIVATE "src"
)

if ("${CMAKE_CXX_COMPILER_ID}" MATCHES "GNU|Clang|IntelLLVM|AppleClang")
  if ("${CMAKE_CXX_COMPILER_FRONTEND_VARIANT}" STREQUAL "MSVC") # clang-cl
    add_compile_options(nightside-launcher INTERFACE /W4056 /W4146 /W4018 /W4056)
  endif ()
  add_compile_options(nightside-launcher INTERFACE -Wno-sign-conversion -Wno-format-security)
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
  add_compile_options(nightside-launcher INTERFACE /W4056 /W4146 /W4018 /W4056)
endif ()

#add_subdirectory(include/launcher)
add_subdirectory(src)

if (WIN32)


    if(MSVC)
        set(subsystem $<IF:$<BOOL:$<CONFIG:Debug>>,CONSOLE,WINDOWS>)
        target_link_options(nightside-launcher PRIVATE
                /SUBSYSTEM:${subsystem}
                /ENTRY:mainCRTStartup
        )
    endif()
endif()
