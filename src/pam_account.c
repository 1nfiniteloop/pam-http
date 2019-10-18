#define PAM_SM_ACCOUNT
#include <security/pam_modules.h>

/**
 * API implementation for PAM service "account"
 * 
 * Ref: http://www.linux-pam.org/Linux-PAM-html/mwg-expected-of-module-acct.html
 */ 

int pam_sm_acct_mgmt(pam_handle_t *pamh, int flags,
				int argc, const char **argv)
{
    return PAM_AUTH_ERR; /* Service not supported */
}