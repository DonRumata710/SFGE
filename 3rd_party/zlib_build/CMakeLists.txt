
set(LIBRARY_NAME zlib)

set(ZLIB_PC ${CMAKE_CURRENT_SOURCE_DIR}/../${LIBRARY_NAME}/zlib.pc)
configure_file( ${CMAKE_CURRENT_SOURCE_DIR}/../${LIBRARY_NAME}/zlib.pc.cmakein
		${ZLIB_PC} @ONLY)
configure_file(	${CMAKE_CURRENT_SOURCE_DIR}/../${LIBRARY_NAME}/zconf.h.cmakein
    ${CMAKE_CURRENT_SOURCE_DIR}/zconf.h @ONLY)

set(SOURCES
    adler32.c
    compress.c
    crc32.c
    deflate.c
    gzclose.c
    gzlib.c
    gzread.c
    gzwrite.c
    inflate.c
    infback.c
    inftrees.c
    inffast.c
    trees.c
    uncompr.c
    zutil.c
)

set(SOURCE_LIST)
foreach(source ${SOURCES})
    LIST(APPEND SOURCE_LIST ${CMAKE_CURRENT_SOURCE_DIR}/../${LIBRARY_NAME}/${source})
endforeach()

set(HEADERS
    crc32.h
    deflate.h
    gzguts.h
    inffast.h
    inffixed.h
    inflate.h
    inftrees.h
    trees.h
    zutil.h
)

set(HEADER_LIST)
foreach(header ${HEADERS})
    LIST(APPEND HEADER_LIST ${CMAKE_CURRENT_SOURCE_DIR}/../${LIBRARY_NAME}/${header})
endforeach()

LIST(APPEND HEADER_LIST ${CMAKE_CURRENT_SOURCE_DIR}/zconf.h)
LIST(APPEND HEADER_LIST ${CMAKE_CURRENT_SOURCE_DIR}/../${LIBRARY_NAME}/zlib.h)


if(CMAKE_COMPILER_IS_GNUCC)
    if(ASM686)
        set(ZLIB_ASMS ../${LIBRARY_NAME}/contrib/asm686/match.S)
    elseif (AMD64)
        set(ZLIB_ASMS ../${LIBRARY_NAME}/contrib/amd64/amd64-match.S)
    endif ()

    if(ZLIB_ASMS)
        add_definitions(-DASMV)
        set_source_files_properties(${ZLIB_ASMS} PROPERTIES LANGUAGE C COMPILE_FLAGS -DNO_UNDERLINE)
    endif()
endif()

if(MSVC)
    if(ASM686)
        ENABLE_LANGUAGE(ASM_MASM)
        set(ZLIB_ASMS
            contrib/masmx86/inffas32.asm
            contrib/masmx86/match686.asm
        )
    elseif (AMD64)
        ENABLE_LANGUAGE(ASM_MASM)
        set(ZLIB_ASMS
            contrib/masmx64/gvmat64.asm
            contrib/masmx64/inffasx64.asm
        )
    endif()

    if(ZLIB_ASMS)
        add_definitions(-DASMV -DASMINF)
    endif()
endif()

if(MINGW)
    add_custom_command(OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/zlib1rc.obj
                       COMMAND ${CMAKE_RC_COMPILER}
                            -D GCC_WINDRES
                            -I ${CMAKE_CURRENT_SOURCE_DIR}
                            -I ${CMAKE_CURRENT_SOURCE_DIR}
                            -o ${CMAKE_CURRENT_SOURCE_DIR}/zlib1rc.obj
                            -i ${CMAKE_CURRENT_SOURCE_DIR}/win32/zlib1.rc)
endif(MINGW)


add_library(${LIBRARY_NAME} STATIC ${SOURCE_LIST} ${HEADER_LIST})
