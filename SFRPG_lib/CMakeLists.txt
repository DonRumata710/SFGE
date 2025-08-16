
set(LIBRARY_NAME SFRPG)

set(SOURCES)
set(HEADERS)

set(CLASSES
    Action
    Actor
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
    World
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

sfge_add_library(${LIBRARY_NAME}
    SOURCES ${SOURCES}
    HEADERS ${HEADERS}
    LINK_LIBS SFGE
)
