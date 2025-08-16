function(sfge_add_library TARGET_NAME)
    cmake_parse_arguments(ARG "" "" "SOURCES;HEADERS;LINK_LIBS" ${ARGN})
    add_library(${TARGET_NAME} SHARED ${ARG_SOURCES} ${ARG_HEADERS})

    target_include_directories(${TARGET_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)

    if(ARG_LINK_LIBS)
        target_link_libraries(${TARGET_NAME} PUBLIC ${ARG_LINK_LIBS})
    endif()

    if(BUILD_STATIC_LIB)
        target_compile_definitions(${TARGET_NAME} PUBLIC EXPORT_${TARGET_NAME}=)
    elseif(WIN32)
        target_compile_definitions(${TARGET_NAME} PRIVATE EXPORT_${TARGET_NAME}=__declspec\(dllexport\))
        target_compile_definitions(${TARGET_NAME} INTERFACE EXPORT_${TARGET_NAME}=__declspec\(dllimport\))
    else()
        target_compile_definitions(${TARGET_NAME} PUBLIC EXPORT_${TARGET_NAME}=__attribute__\(\(visibility\(\"default\"\)\)\))
    endif()
endfunction()

function(sfge_add_executable TARGET_NAME)
    cmake_parse_arguments(ARG "" "" "SOURCES;HEADERS;LINK_LIBS;INCLUDE_DIRS;LINK_DIRS" ${ARGN})
    add_executable(${TARGET_NAME} ${ARG_SOURCES} ${ARG_HEADERS})

    target_include_directories(${TARGET_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include ${ARG_INCLUDE_DIRS})

    if(ARG_LINK_DIRS)
        target_link_directories(${TARGET_NAME} PRIVATE ${ARG_LINK_DIRS})
    endif()

    if(ARG_LINK_LIBS)
        target_link_libraries(${TARGET_NAME} PRIVATE ${ARG_LINK_LIBS})
    endif()

    install(TARGETS ${TARGET_NAME} DESTINATION bin)
endfunction()

function(sfge_add_test TARGET_NAME)
    cmake_parse_arguments(ARG "" "" "SOURCES;HEADERS;LINK_LIBS;INCLUDE_DIRS;LINK_DIRS" ${ARGN})
    list(APPEND ARG_LINK_LIBS Catch2::Catch2)
    sfge_add_executable(${TARGET_NAME}
        SOURCES ${ARG_SOURCES}
        HEADERS ${ARG_HEADERS}
        LINK_LIBS ${ARG_LINK_LIBS}
        INCLUDE_DIRS ${ARG_INCLUDE_DIRS}
        LINK_DIRS ${ARG_LINK_DIRS}
    )
    add_test(NAME ${TARGET_NAME} COMMAND ${TARGET_NAME})
endfunction()
