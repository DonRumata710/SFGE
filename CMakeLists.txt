
cmake_minimum_required(VERSION 3.16)

project(SFGE)

if (EXISTS "${CMAKE_SOURCE_DIR}/local.cmake")
    include ("local.cmake")
endif()

if(NOT "${LOCAL_HINTS}" STREQUAL "")
    if(NOT DEFINED TARGET_ARCH)
        if(CMAKE_SIZEOF_VOID_P EQUAL 4)
            set(TARGET_ARCH "x32")
        else()
            set(TARGET_ARCH "x64")
        endif()
    endif()

    if(TARGET_ARCH STREQUAL "x32")
        set(_ARCH_SUFFIX "32")
    else()
        set(_ARCH_SUFFIX "64")
    endif()

    if(WIN32)
        set(_OS_SUFFIX "win")
    else()
        set(_OS_SUFFIX "linux")
    endif()

    if(MINGW)
        set(_COMPILE_FLAG "-mingw${_ARCH_SUFFIX}")
    endif()

    string(APPEND LOCAL_HINTS "/${_OS_SUFFIX}${_ARCH_SUFFIX}${_COMPILE_FLAG}/")

    if("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
        string(APPEND LOCAL_HINTS "Debug/")
    else()
        string(APPEND LOCAL_HINTS "Release/")
    endif()

    list(APPEND CMAKE_PREFIX_PATH ${LOCAL_HINTS})

    file(GLOB packages RELATIVE ${LOCAL_HINTS} ${LOCAL_HINTS}/*)

    foreach(package ${packages})
        if(NOT EXISTS "${CMAKE_SOURCE_DIR}/3rdparty/${package}")
            list(APPEND CMAKE_PREFIX_PATH ${LOCAL_HINTS}/${package})
            string(TOUPPER "${package}" uname)
            set(${uname}_ROOT_DIR "${LOCAL_HINTS}${package}" CACHE PATH "path to ${package}")
            set(${package}_ROOT_DIR "${LOCAL_HINTS}${package}" CACHE PATH "path to ${package}")
            message("Added ${package} to search paths")
        endif()
    endforeach()
    message("Prefix path: ${CMAKE_PREFIX_PATH}")
endif()

if(MSVC)
    add_definitions(-D_CRT_SECURE_NO_DEPRECATE -D_SCL_SECURE_NO_WARNINGS)
endif()

macro(set_option var type default docstring)
    if(NOT DEFINED ${var})
        set(${var} ${default})
    endif()
    set(${var} ${${var}} CACHE ${type} ${docstring} FORCE)
endmacro()

set(SFML_STATIC_LIBRARIES FALSE)
set(CMAKE_CXX_STANDARD 20)

get_property(importTargets DIRECTORY "${CMAKE_SOURCE_DIR}" PROPERTY IMPORTED_TARGETS)

find_package(SFML COMPONENTS system window graphics audio)
find_package(Catch2)

get_property(importTargetsAfter DIRECTORY "${CMAKE_SOURCE_DIR}" PROPERTY IMPORTED_TARGETS)
list(REMOVE_ITEM importTargetsAfter ${importTargets})

message("imported targets: ${importTargetsAfter}")

add_subdirectory(SFGE_lib)
add_subdirectory(SFGE_test_app)
add_subdirectory(SFRPG_lib)
add_subdirectory(SFRPG_unittest)
add_subdirectory(SFRPG_map_editor)
