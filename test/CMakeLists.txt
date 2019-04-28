# Root cmake directory for the tests.
ADD_SUBDIRECTORY(${CMAKE_CURRENT_SOURCE_DIR}/common-test)
ADD_SUBDIRECTORY(${CMAKE_CURRENT_SOURCE_DIR}/unit-test)
ADD_SUBDIRECTORY(${CMAKE_CURRENT_SOURCE_DIR}/graphic-test)

# Tests the internal states.
ADD_TEST(
        NAME unit-assert
        COMMAND sprite-batch-cunit)
SET_TESTS_PROPERTIES(unit-assert PROPERTIES DEPENDS sprite-batch-cunit)

# Tests the graphic results and its performance.
ADD_TEST(
        NAME graphic-testing
        COMMAND sprite-batch-graphic)
SET_TESTS_PROPERTIES(graphic-testing PROPERTIES DEPENDS sprite-batch-graphic)