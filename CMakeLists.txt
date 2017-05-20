
cmake_minimum_required(VERSION 3.0)

project(SFGE)

if(MSVC)
    add_definitions(-D_CRT_SECURE_NO_DEPRECATE -D_SCL_SECURE_NO_WARNINGS)
endif()

macro(set_option var type default docstring)
    if(NOT DEFINED ${var})
        set(${var} ${default})
    endif()
    set(${var} ${${var}} CACHE ${type} ${docstring} FORCE)
endmacro()

set_option(SFML_ROOT STRING "${CMAKE_SOURCE_DIR}/../SFML" "Set SFML folder")
set_option(CATCH_ROOT STRING "${CMAKE_SOURCE_DIR}/../Catch" "Set Catch folder")

set(SFML_STATIC_LIBRARIES TRUE)

add_subdirectory(SFGE_lib)
add_subdirectory(SFRPG_lib)
add_subdirectory(SFRPG_unittest)
add_subdirectory(TestApplication)
