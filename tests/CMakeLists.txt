include(gmock)
include(httpmockserver)

add_subdirectory(http_auth)
add_subdirectory(http_client)
add_subdirectory(options)

# Workaround since "make test" doesn't build tests.
add_custom_target(test_all COMMAND ${CMAKE_CTEST_COMMAND} DEPENDS
    http_auth_test
    http_client_test
    options_test
)