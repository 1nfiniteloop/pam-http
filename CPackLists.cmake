set(CPACK_GENERATOR "DEB")
set(CPACK_PACKAGE_VERSION "${PROJECT_VERSION}")
set(CPACK_PACKAGE_CONTACT "Lars Gunnarsson <gunnarsson.lars@gmail.com>")
set(CPACK_PACKAGE_DESCRIPTION "Pluggable authentication module for authentication over https")
set(CPACK_DEBIAN_PACKAGE_HOMEPAGE "https://github.com/1nfiniteloop/pam-http")
set(CPACK_DEBIAN_PACKAGE_DEPENDS "libcurl4,libpam0g")

include(CPack)