if(NOT THIRD_PARTY)
    message(FATAL_ERROR "Missing variable THIRD_PARTY")
endif()

set(GTEST_DIR ${THIRD_PARTY}/googletest/googletest)
set(GMOCK_DIR ${THIRD_PARTY}/googletest/googlemock)

set(TARGET_NAME "gmock")
add_library(${TARGET_NAME} STATIC IMPORTED)
set_property(TARGET ${TARGET_NAME} PROPERTY INTERFACE_INCLUDE_DIRECTORIES
    ${GMOCK_DIR}/include
    ${GTEST_DIR}/include
)
set_target_properties(${TARGET_NAME} PROPERTIES
    IMPORTED_LOCATION ${GMOCK_DIR}/build/libgmock.a
)
