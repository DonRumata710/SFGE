
set(APPLICATION_NAME SFRPG_unittest)

set(TEST_FILES
    CollisionTest
)

set(SOURCES)
foreach(test ${TEST_FILES})
    LIST(APPEND SOURCES ${PROJECT_SOURCE_DIR}/${APPLICATION_NAME}/${test}.cpp)
endforeach()

include_directories(${PROJECT_SOURCE_DIR}/include ${CATCH_ROOT}/include )
link_directories(${SFML_ROOT}/lib)

add_executable(${APPLICATION_NAME} ${SOURCES})

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/CMakeModules" ${CMAKE_MODULE_PATH})

find_package(SFML 2 REQUIRED system window graphics audio)
if(SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(${APPLICATION_NAME} SFRPG SFGE ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
endif()

install(TARGETS ${APPLICATION_NAME} DESTINATION bin)