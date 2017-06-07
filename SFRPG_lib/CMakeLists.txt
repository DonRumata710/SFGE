
set(LIBRARY_NAME SFRPG)

set(SOURCES)
set(HEADERS)

set(CLASSES
    Action
    Actor
	Camera
    Collision
    DynamicObject
    InteractiveObject
    MapLoader
    MapManager
    MapObject
	MapSaver
    MapSector
    StaticObject
    Way
    WayPoint
)

set(PRIVATE_CLASSES
	SectorLoader
)

set(UTILITY_HEADERS
)

set(SFGE_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include/)
set(SFRPG_INCLUDE_DIR ${SFGE_INCLUDE_DIR}/${LIBRARY_NAME}/)
set(SFRPG_LIB_DIR ${PROJECT_SOURCE_DIR}/${LIBRARY_NAME}_lib/)

foreach(class ${CLASSES})
    LIST(APPEND SOURCES ${SFGE_LIB_DIR}${class}.cpp)
    LIST(APPEND HEADERS ${SFRPG_INCLUDE_DIR}${class}.h)
endforeach()

foreach(class ${PRIVATE_CLASSES})
    LIST(APPEND SOURCES ${SFGE_LIB_DIR}${class}.cpp)
    LIST(APPEND HEADERS ${SFGE_LIB_DIR}${class}.h)
endforeach()

foreach(header ${UTILITY_HEADERS})
  LIST(APPEND HEADERS ${SFRPG_INCLUDE_DIR}${header}.h)
endforeach()

include_directories(${SFRPG_INCLUDE_DIR} ${SFGE_INCLUDE_DIR}  ${SFML_ROOT}/include)
add_definitions(-DSFML_STATIC)

add_library(${LIBRARY_NAME} STATIC ${SOURCES} ${HEADERS})
