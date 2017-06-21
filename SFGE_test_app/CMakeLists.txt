
set(APPLICATION_NAME SFGE_test_app)

set(SOURCES
    ${PROJECT_SOURCE_DIR}/${APPLICATION_NAME}/Source.cpp
)

include_directories(${PROJECT_SOURCE_DIR}/include)
link_directories(${SFML_ROOT}/lib ${ZLIB_ROOT}/lib ${MINIZIP_ROOT}/lib)

add_executable(${APPLICATION_NAME} ${SOURCES})

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/CMakeModules" ${CMAKE_MODULE_PATH})

find_package(SFML 2 REQUIRED system window graphics audio)
if(SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(${APPLICATION_NAME} SFGE ${SFML_LIBRARIES} ${SFML_DEPENDENCIES} minizip zlib)
endif()

if(WIN32)
    configure_file(${CMAKE_SOURCE_DIR}/${APPLICATION_NAME}/OpenAL32.dll ${CMAKE_BINARY_DIR}/${APPLICATION_NAME}/OpenAL32.dll COPYONLY)
endif()
file(COPY ${CMAKE_SOURCE_DIR}/${APPLICATION_NAME}/media DESTINATION ${CMAKE_BINARY_DIR}/${APPLICATION_NAME}/)

install(TARGETS ${APPLICATION_NAME} DESTINATION bin)
