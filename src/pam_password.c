#define PAM_SM_PASSWORD
#include <security/pam_modules.h>

/**
 * API implementation for PAM service "password".
 * 
 * Ref: http://www.linux-pam.org/Linux-PAM-html/mwg-expected-of-module-chauthtok.html
 */

int pam_sm_chauthtok(pam_handle_t *pamh, int flags,
				int argc, const char **argv)
{
    return PAM_AUTHTOK_ERR; /* Service not supported */
}