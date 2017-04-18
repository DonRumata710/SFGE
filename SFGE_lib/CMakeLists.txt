
cmake_minimum_required(VERSION 3.5)

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
    Widget
)

set(PRIVATE_CLASSES
    ResourceLoader
    ResourceParser
    TextParser
)

set(UTILITY_HEADERS
    AnimationDesc
    DistortionMesh
    ParticleSystem
    SpriteDesc
    StringTable
    Unicode
)

set(SFGE_LIB_DIR ./SFGE_lib)

foreach(class ${CLASSES})
    LIST(APPEND SOURCES ${PROJECT_SOURCE_DIR}/SFGE_lib/${class}.cpp)
    LIST(APPEND HEADERS ${PROJECT_SOURCE_DIR}/include/${class}.h)
endforeach()

foreach(class ${PRIVATE_CLASSES})
    LIST(APPEND SOURCES ${PROJECT_SOURCE_DIR}/SFGE_lib/${class}.cpp)
    LIST(APPEND HEADERS ${PROJECT_SOURCE_DIR}/SFGE_lib/${class}.h)
endforeach()

foreach(header ${UTILITY_HEADERS})
    LIST(APPEND HEADERS ${PROJECT_SOURCE_DIR}/include/${header}.h)
endforeach()

include_directories(${PROJECT_SOURCE_DIR}/include ${SFML_ROOT}/include)
add_definitions(-DSFML_STATIC)

add_library(SFGE_lib STATIC ${SOURCES} ${HEADERS})
