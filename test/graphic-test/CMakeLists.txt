# gcc compiler options.
IF((CMAKE_COMPILER_IS_GNUCC) AND NOT CMAKE_COMPILER_IS_MINGOW)

    # Compiling language standard.
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

# Set c++ language version required for the project.
IF( CMAKE_COMPILER_IS_GNUCXX )
    SET(LIBSTDC++_LIBRARIES -std=c++11)
ENDIF( CMAKE_COMPILER_IS_GNUCXX )
ENABLE_LANGUAGE(CXX)

# Include directory for hpm declaration.
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/../../include)
# Include header directory for this program.
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/include)
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/../common-test)

# Source files for the hpmassert program.
FILE(GLOB unitsrc   ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
                    ${CMAKE_CURRENT_SOURCE_DIR}/src/Scene/*.cpp)

# Executable hpm assert program.
ADD_EXECUTABLE(sprite-batch-graphic ${unitsrc})
TARGET_LINK_LIBRARIES(sprite-batch-graphic -lm -lcheck -lpthread -lrt -lsubunit spb -lSDL2 -lGLEW sprite-batch-test-common)
SET_TARGET_PROPERTIES(sprite-batch-graphic PROPERTIES LINKER_LANGUAGE CXX)

#
ADD_EXECUTABLE(sprite-batch-graphic-quad ${unitsrc})
TARGET_LINK_LIBRARIES(sprite-batch-graphic-quad -lm -lcheck -lpthread -lrt -lsubunit spb-quad -lSDL2 -lGLEW sprite-batch-test-common)
SET_TARGET_PROPERTIES(sprite-batch-graphic-quad PROPERTIES LINKER_LANGUAGE CXX)