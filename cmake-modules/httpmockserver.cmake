if(NOT THIRD_PARTY)
    message(FATAL_ERROR "Missing variable THIRD_PARTY")
endif()

set(TARGET_NAME "httpmockserver")

add_library(${TARGET_NAME} STATIC IMPORTED)
set_target_properties(${TARGET_NAME} PROPERTIES
    IMPORTED_LOCATION ${THIRD_PARTY}/httpmockserver/build/src/libhttpmockserver.a
    INTERFACE_INCLUDE_DIRECTORIES ${THIRD_PARTY}/httpmockserver/include
    INTERFACE_LINK_LIBRARIES microhttpd
)