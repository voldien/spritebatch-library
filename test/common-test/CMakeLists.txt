# gcc compiler options.
IF((CMAKE_COMPILER_IS_GNUCC) AND NOT CMAKE_COMPILER_IS_MINGOW)

    # Compiling language standard.
    ADD_DEFINITIONS(-std=c11)
    ADD_DEFINITIONS(-w)

    # Check build target.
    IF (CMAKE_BUILD_TYPE STREQUAL "Release")
        MESSAGE(STATUS "Compile for release.")
        ADD_DEFINITIONS(-DNDEBUG -O2)
        SET(CMAKE_RELEASE TRUE)
    ELSEIF( CMAKE_BUILD_TYPE STREQUAL "Debug")
        MESSAGE(STATUS "Compile for debug.")
        ADD_DEFINITIONS(-D_DEBUG)
        ADD_DEFINITIONS(-g3)
        SET(CMAKE_DEBUG TRUE)
    ENDIF()

ELSEIF(MSVC)
    # Enable multi-core complication with MSVC
    ADD_DEFINITIONS(/MP)
ENDIF()

# Include directory for hpm declaration.
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/../../include)
# Include header directory for this program.
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/include)

# Source files for the hpmassert program.
FILE(GLOB testsrc  ${CMAKE_CURRENT_SOURCE_DIR}/*.c)

# Executable hpm assert program.
ADD_LIBRARY(sprite-batch-test-common ${testsrc})
TARGET_LINK_LIBRARIES(sprite-batch-test-common -lSDL2 ${OPENGL_LIBRARIES})