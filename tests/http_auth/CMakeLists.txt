set(UNITTEST_NAME http_auth_test)
set(SOURCES
    ../gtest_main.cpp
    http_auth_test.cpp
    
    # Code under test:
    ${SOURCE_DIR}/http_auth.c
    ${SOURCE_DIR}/http_client.c
    ${SOURCE_DIR}/options.c
)
add_executable(${UNITTEST_NAME} ${SOURCES})
add_test(NAME ${UNITTEST_NAME} COMMAND ${UNITTEST_NAME})
target_include_directories(${UNITTEST_NAME} PRIVATE
    ${INCLUDE_DIR}
)
target_link_libraries(${UNITTEST_NAME}
    gmock
    httpmockserver
    curl
)

# linker flag "-pthread" needed with gmock
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -pthread")