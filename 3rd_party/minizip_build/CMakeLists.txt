
set(LIBRARY_NAME minizip)

set(SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/../${LIBRARY_NAME}/crypt.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../${LIBRARY_NAME}/ioapi.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../${LIBRARY_NAME}/ioapi_buf.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../${LIBRARY_NAME}/ioapi_mem.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../${LIBRARY_NAME}/unzip.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../${LIBRARY_NAME}/zip.c"
)

set(HEADERS
    "${CMAKE_CURRENT_SOURCE_DIR}/../${LIBRARY_NAME}/crypt.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/../${LIBRARY_NAME}/ioapi.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/../${LIBRARY_NAME}/ioapi_buf.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/../${LIBRARY_NAME}/ioapi_mem.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/../${LIBRARY_NAME}/unzip.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/../${LIBRARY_NAME}/zip.h"
)

if(WIN32)
    list(APPEND SOURCES "../${LIBRARY_NAME}/iowin32.c")
    list(APPEND HEADERS "../${LIBRARY_NAME}/iowin32.h")
    add_definitions(-D_CRT_SECURE_NO_DEPRECATE)
endif()

if(UNIX)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fPIC -O3")
    add_definitions(-D__USE_FILE_OFFSET64)
    add_definitions(-D__USE_LARGEFILE64)
    add_definitions(-D_LARGEFILE64_SOURCE)
    add_definitions(-D_FILE_OFFSET_BIT=64)
endif()

include_directories(${ZLIB_ROOT})

add_library(${LIBRARY_NAME} STATIC ${SOURCES} ${HEADERS})
