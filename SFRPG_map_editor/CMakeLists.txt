
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

sfge_add_executable(${APPLICATION_NAME}
    SOURCES ${SOURCES}
    HEADERS ${HEADERS}
    LINK_LIBS SFRPG SFGE
)

file(COPY ${CMAKE_SOURCE_DIR}/${APPLICATION_NAME}/media DESTINATION ${CMAKE_BINARY_DIR}/${APPLICATION_NAME}/)
