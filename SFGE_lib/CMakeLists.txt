
set(LIBRARY_NAME SFGE)

set(SOURCES)
set(HEADERS)

set(CLASSES
    Animation
    ArchiveManager
    Button
    CheckBox
    PullDownMenu
    Err
    Field
    File
    FileInputStream
    FileOutputStream
    Frame
    GEDevice
    GridBox
    GuiManager
    Label
    LineEdit
    MemoryInputStream
    MemoryOutputStream
    MenuBar
    Panel
    PullDownMenu
    RenderRect
    ResourceManager
    Slider
    StackedWidget
    StringTable
    TextList
    TextParser
    Widget
    WidgetCollection
    WidgetStyle
)

set(PRIVATE_CLASSES
    ResourceLoader
    ResourceParser
)

set(UTILITY_HEADERS
    AnimationDesc
    Config
    DataOutputStream
    DistortionMesh
    GuiElement
    MenuItem
    ParticleSystem
    ResourceInputStream
    SpriteDesc
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

add_library(${LIBRARY_NAME} SHARED ${SOURCES} ${HEADERS})

target_include_directories(${LIBRARY_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)

target_link_libraries(${LIBRARY_NAME} PUBLIC sfml-system sfml-window sfml-graphics sfml-audio minizip)

if(BUILD_STATIC_LIB)
    target_compile_definitions(${LIBRARY_NAME} PUBLIC
        EXPORT_${LIBRARY_NAME}=
    )
elseif(WIN32)
    target_compile_definitions(${LIBRARY_NAME} PRIVATE
        EXPORT_${LIBRARY_NAME}=__declspec\(dllexport\)
    )
    target_compile_definitions(${LIBRARY_NAME} INTERFACE
        EXPORT_${LIBRARY_NAME}=__declspec\(dllimport\)
    )
else()
    target_compile_definitions(${LIBRARY_NAME} PUBLIC
        EXPORT_${LIBRARY_NAME}=__attribute__\(\(visibility\(\"default\"\)\)\)
    )
endif()
