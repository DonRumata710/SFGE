
cmake_minimum_required(VERSION 3.5)

macro(sfge_set_option var type default docstring)
    if(NOT DEFINED ${var})
        set(${var} ${default})
    endif()
    set(${var} ${${var}} CACHE ${type} ${docstring} FORCE)
endmacro()

project(SFGE)

if(MSVC)
    add_definitions(-D_CRT_SECURE_NO_DEPRECATE -D_SCL_SECURE_NO_WARNINGS)
endif()

sfge_set_option(SFML_ROOT STRING "${CMAKE_SOURCE_DIR}/../SFML" "Set SFML folder")

add_subdirectory(SFGE_lib)
add_subdirectory(TestApplication)
