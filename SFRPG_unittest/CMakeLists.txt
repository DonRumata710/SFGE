
set(APPLICATION_NAME SFRPG_unittest)

set(TEST_FILES
    CollisionTest
    MapLoadingTest
    WaySearchTest
    Main
)

set(SOURCES)
foreach(test ${TEST_FILES})
    LIST(APPEND SOURCES ${PROJECT_SOURCE_DIR}/${APPLICATION_NAME}/${test}.cpp)
endforeach()

sfge_add_test(${APPLICATION_NAME}
    SOURCES ${SOURCES}
    LINK_LIBS SFRPG
)

if(WIN32)
    configure_file(${CMAKE_SOURCE_DIR}/${APPLICATION_NAME}/OpenAL32.dll ${CMAKE_BINARY_DIR}/${APPLICATION_NAME}/OpenAL32.dll COPYONLY)
endif()
