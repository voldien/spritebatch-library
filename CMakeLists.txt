CMAKE_MINIMUM_REQUIRED(VERSION 2.8.12)
PROJECT(spritebatch)

#	build shared/dynamic library option
OPTION(BUILD_SHARED_LIBS "Build package with shared libraries." ON)
IF(NOT BUILD_SHARED_LIBS)
    set(CMAKE_EXE_LINKER_FLAGS "-static")
    set(LINK_SEARCH_START_STATIC TRUE)
ENDIF()

# hpm version setup.
SET(SPB_VERSION_MAJOR 0)
SET(SPB_VERSION_MINOR 4)
SET(SPB_VERSION_REVISION 0)
SET(SPB_VERSION_STATE a)
SET(SPB_VERSION ${SPB_VERSION_MAJOR}.${SPB_VERSION_MINOR}${SPB_VERSION_STATE}${SPB_VERSION_REVISION} )
ADD_DEFINITIONS(-DSPB_VERSION="${SPB_VERSION}")

# gcc compiler flags
IF((CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX) AND NOT CMAKE_COMPILER_IS_MINGW)
    IF (BUILD_SHARED_LIBS AND CMAKE_SIZEOF_VOID_P EQUAL 8) # -fPIC is only required
        SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")
    ENDIF()

    ADD_DEFINITIONS( -Wall -w -fpermissive -Wfatal-errors)


    IF (CMAKE_BUILD_TYPE STREQUAL "Release")
        MESSAGE(STATUS "Compile for release.")
        ADD_DEFINITIONS( -DNDEBUG )
        ADD_DEFINITIONS( -O2 )
        SET(CMAKE_RELEASE TRUE)
    ELSE()
        MESSAGE(STATUS "Compile for debug.")
        ADD_DEFINITIONS( -D_DEBUG )
        ADD_DEFINITIONS( -g3 -O0 )
        SET(CMAKE_DEBUG TRUE)
    ENDIF()
ENDIF()

# Include OpenGL and FreeType.
FIND_PACKAGE(Freetype REQUIRED)
SET(OpenGL_GL_PREFERENCE "GLVND")
FIND_PACKAGE(OpenGL REQUIRED)
INCLUDE_DIRECTORIES(${FREETYPE_INCLUDE_DIRS})
INCLUDE_DIRECTORIES(${OPENGL_INCLUDE_DIR})

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/include)
FILE(GLOB src   ${CMAKE_CURRENT_SOURCE_DIR}/src/font.c
                ${CMAKE_CURRENT_SOURCE_DIR}/src/geometry.c
                ${CMAKE_CURRENT_SOURCE_DIR}/src/gl_func.c
                ${CMAKE_CURRENT_SOURCE_DIR}/src/matrix.c
                ${CMAKE_CURRENT_SOURCE_DIR}/src/shader.c
                ${CMAKE_CURRENT_SOURCE_DIR}/src/shaders.c
                ${CMAKE_CURRENT_SOURCE_DIR}/src/sprite.c
                ${CMAKE_CURRENT_SOURCE_DIR}/src/texture.c)
FILE(GLOB quad-src   ${CMAKE_CURRENT_SOURCE_DIR}/src/font.c
        ${CMAKE_CURRENT_SOURCE_DIR}/src/geometry.c
        ${CMAKE_CURRENT_SOURCE_DIR}/src/gl_func.c
        ${CMAKE_CURRENT_SOURCE_DIR}/src/matrix.c
        ${CMAKE_CURRENT_SOURCE_DIR}/src/shader.c
        ${CMAKE_CURRENT_SOURCE_DIR}/src/shaders.c
        ${CMAKE_CURRENT_SOURCE_DIR}/src/sprite_quad.c
        ${CMAKE_CURRENT_SOURCE_DIR}/src/texture.c)
FILE(GLOB headers ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h)

# Create executable target.
ADD_LIBRARY(spb ${src})
TARGET_LINK_LIBRARIES(spb ${OPENGL_LIBRARIES} ${FREETYPE_LIBRARIES})

ADD_LIBRARY(spb-quad ${quad-src})
TARGET_LINK_LIBRARIES(spb-quad ${OPENGL_LIBRARIES} ${FREETYPE_LIBRARIES})

# Install the target.
INSTALL(TARGETS spb DESTINATION lib)
FILE(GLOB install_headers ${CMAKE_CURRENT_SOURCE_DIR}/include/def.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/font.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/shader.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/sprite.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/texture.h)
INSTALL (FILES ${install_headers} DESTINATION include/spb)

# Testing directory
ADD_SUBDIRECTORY(${CMAKE_CURRENT_SOURCE_DIR}/test)

IF( UNIX )

    # Create distribution tarball.
    SET( TARGETDIR "${PROJECT_NAME}-${VERSION}")
    ADD_CUSTOM_TARGET(	distribution
            COMMAND mkdir -p ${TARGETDIR}
            COMMAND cp -r ${CMAKE_CURRENT_SOURCE_DIR}/src ${CMAKE_CURRENT_SOURCE_DIR}/include ${CMAKE_CURRENT_SOURCE_DIR}/CMakeLists.txt ${CMAKE_CURRENT_SOURCE_DIR}/LICENSE ${TARGETDIR}
            COMMAND tar cf - ${TARGETDIR} | gzip -c > ${TARGETDIR}.tar.gz
            COMMAND rm -r ${TARGETDIR} )
ELSE()

ENDIF()

FIND_PACKAGE(PythonInterp)
IF(PYTHONINTERP_FOUND)
    ADD_DEPENDENCIES(spb compile-shader )
    ADD_CUSTOM_TARGET( compile-shader
            COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/utils/glsl2CString.py ${CMAKE_CURRENT_SOURCE_DIR}/shader/)
ENDIF()
