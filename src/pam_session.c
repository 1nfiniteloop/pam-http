#define PAM_SM_SESSION
#include <security/pam_modules.h>

/** 
 * API implementations for PAM service "session".
 * 
 * Ref: http://www.linux-pam.org/Linux-PAM-html/mwg-expected-of-module-session.html
 */

int pam_sm_open_session(pam_handle_t *pamh, int flags,
				   int argc, const char **argv)
{
    return PAM_SESSION_ERR; /* Service not supported */
}

int pam_sm_close_session(pam_handle_t *pamh, int flags,
				    int argc, const char **argv)
{
    return PAM_SESSION_ERR; /* Service not supported */
}
