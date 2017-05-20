
set(LIBRARY_NAME SFGE)

set(SOURCES)
set(HEADERS)

set(CLASSES
    Animation
    Button
    CheckBox
    Err
    Field
    File
    Frame
    GEDevice
    GridBox
    GuiElement
    GuiManager
    Label
    LineEdit
    Panel
    RenderRect
    ResourceManager
    Slider
    StackedWidget
    TextList
    TextParser
    Widget
)

set(PRIVATE_CLASSES
    ResourceLoader
    ResourceParser
)

set(UTILITY_HEADERS
    AnimationDesc
    DistortionMesh
    ParticleSystem
    SpriteDesc
    StringTable
    Unicode
)

set(SFGE_LIB_DIR ${PROJECT_SOURCE_DIR}/${LIBRARY_NAME}_lib/)
set(SFGE_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include/${LIBRARY_NAME}/)

foreach(class ${CLASSES})
    LIST(APPEND SOURCES ${SFGE_LIB_DIR}${class}.cpp)
    LIST(APPEND HEADERS ${SFGE_INCLUDE_DIR}${class}.h)
endforeach()

foreach(class ${PRIVATE_CLASSES})
    LIST(APPEND SOURCES ${SFGE_LIB_DIR}${class}.cpp)
    LIST(APPEND HEADERS ${SFGE_LIB_DIR}${class}.h)
endforeach()

foreach(header ${UTILITY_HEADERS})
    LIST(APPEND HEADERS ${SFGE_INCLUDE_DIR}${header}.h)
endforeach()

include_directories(${SFGE_INCLUDE_DIR} ${SFML_ROOT}/include)
add_definitions(-DSFML_STATIC)

add_library(${LIBRARY_NAME} STATIC ${SOURCES} ${HEADERS})
