
set(APPLICATION_NAME SFRPG_map_editor)

set(HEADER_FILES
    Common
)

set(CLASSES
    Application
    EditField
    FSBrowserDialog
    OpenFileDialog
    SaveFileDialog
)

set(SOURCE_FILES
    Main
)

set(HEADERS)
set(SOURCES)

foreach(header ${HEADER_FILES})
    LIST(APPEND HEADERS ${PROJECT_SOURCE_DIR}/${APPLICATION_NAME}/${header}.h)
endforeach()

foreach(class ${CLASSES})
    LIST(APPEND HEADERS ${PROJECT_SOURCE_DIR}/${APPLICATION_NAME}/${class}.h)
    LIST(APPEND SOURCES ${PROJECT_SOURCE_DIR}/${APPLICATION_NAME}/${class}.cpp)
endforeach()

foreach(source ${SOURCE_FILES})
    LIST(APPEND SOURCES ${PROJECT_SOURCE_DIR}/${APPLICATION_NAME}/${source}.cpp)
endforeach()

include_directories(${PROJECT_SOURCE_DIR}/include ${CATCH_ROOT}/include )
link_directories(${SFML_ROOT}/lib)

add_executable(${APPLICATION_NAME} ${SOURCES} ${HEADERS})

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/CMakeModules" ${CMAKE_MODULE_PATH})

include_directories(${SFML_INCLUDE_DIR})
target_link_libraries(${APPLICATION_NAME} SFRPG SFGE)

file(COPY ${CMAKE_SOURCE_DIR}/${APPLICATION_NAME}/media DESTINATION ${CMAKE_BINARY_DIR}/${APPLICATION_NAME}/)

install(TARGETS ${APPLICATION_NAME} DESTINATION bin)
