
cmake_minimum_required(VERSION 3.1)

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

set_option(SFML_ROOT STRING "${CMAKE_SOURCE_DIR}/3rd_party/SFML" "Set SFML folder")
set_option(CATCH_ROOT STRING "${CMAKE_SOURCE_DIR}/3rd_party/Catch" "Set Catch folder")
set_option(ZLIB_ROOT STRING "${CMAKE_SOURCE_DIR}/3rd_party/zlib" "Set zlib folder")
set_option(MINIZIP_ROOT STRING "${CMAKE_SOURCE_DIR}/3rd_party/minizip" "Set minizip folder")

if (WIN32)
    set(SFML_STATIC_LIBRARIES TRUE)
else()
    set(SFML_STATIC_LIBRARIES FALSE)
    set(CMAKE_CXX_STANDARD 11)
endif()


add_subdirectory(3rd_party/zlib_build)
add_subdirectory(3rd_party/minizip_build)
add_subdirectory(SFGE_lib)
add_subdirectory(SFGE_test_app)
add_subdirectory(SFRPG_lib)
add_subdirectory(SFRPG_unittest)
add_subdirectory(SFRPG_map_editor)
