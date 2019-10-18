set(LIBRARY_NAME "pam_http")
set(SOURCES
    http_auth.c
    http_client.c
    options.c
    pam_account.c
    pam_auth.c
    pam_password.c
    pam_session.c
)
add_library(${LIBRARY_NAME} SHARED ${SOURCES})
set(CMAKE_SHARED_LIBRARY_PREFIX "")  # pam-plugin shall not be prefixed with lib
target_include_directories(${LIBRARY_NAME} PRIVATE ${INCLUDE_DIR})
target_link_libraries(${LIBRARY_NAME} curl)
install(TARGETS ${LIBRARY_NAME} DESTINATION /lib/x86_64-linux-gnu/security)
