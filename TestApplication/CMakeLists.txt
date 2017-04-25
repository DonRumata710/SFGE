
set(SOURCE_EXE ${PROJECT_SOURCE_DIR}/TestApplication/Source.cpp)

include_directories(${PROJECT_SOURCE_DIR}/include)
link_directories(${SFML_ROOT}/lib)

add_executable(TestApplication ${SOURCE_EXE})

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/CMakeModules" ${CMAKE_MODULE_PATH})
set(SFML_STATIC_LIBRARIES TRUE)

find_package(SFML 2 REQUIRED system window graphics audio)
if(SFML_FOUND)
  include_directories(${SFML_INCLUDE_DIR})
  target_link_libraries(TestApplication SFGE ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
endif()

install(TARGETS TestApplication DESTINATION bin)
