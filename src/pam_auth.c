#include <string.h> /* fprintf */
#include <stdio.h> /* strdup */
#include <stdlib.h>
#include <pwd.h> /* struct passwd */
#define PAM_SM_AUTH
#include <security/pam_modules.h>
#include <security/pam_ext.h>
#include <security/pam_modutil.h> /* pam_modutil_getpwnam()*/

#include "pam-http/options.h" /* Options */
#include "pam-http/http_auth.h"

#define ENDLINE "\n"

#ifdef DEBUG
#define PAM_DEBUG(fmt...) fprintf(stderr, "DEBUG: " fmt);
#else
#define PAM_DEBUG(fmt...)
#endif

/**
 * API implementation for PAM service "auth".
 * 
 * Ref: http://www.linux-pam.org/Linux-PAM-html/mwg-expected-of-module-auth.html 
 */

typedef int PamStatus;


static PamStatus get_service_name(pam_handle_t *pamh, const char** serviceName) {
    PamStatus status;
    int retval = pam_get_item(pamh, PAM_SERVICE, (const void **) serviceName);
    if (retval != PAM_SUCCESS || serviceName == NULL || *serviceName == NULL) {
        status = PAM_AUTHINFO_UNAVAIL;
        PAM_DEBUG("Service name lookup failed" ENDLINE);
    } else {
        status = PAM_SUCCESS;
    }
    return status;
}

static PamStatus get_user_name(pam_handle_t *pamh, const char** userName) {
    PamStatus status;
    int retval = pam_get_user(pamh, userName, NULL);
    if (retval != PAM_SUCCESS || userName == NULL || *userName == NULL) {
        status = PAM_AUTHINFO_UNAVAIL;
        PAM_DEBUG("User name lookup failed" ENDLINE);
    } else {
        status = PAM_SUCCESS;
    }
    return status;
}

static PamStatus get_user_id(pam_handle_t *pamh, const char* userName, char* userId) {
    PamStatus status;
    struct passwd *pw = pam_modutil_getpwnam(pamh, userName);
    if (pw == NULL) {
        status = PAM_USER_UNKNOWN;
        PAM_DEBUG("User %s does not exist" ENDLINE, userName);
    } else {
        sprintf(userId, "%u", pw->pw_uid);
        status = PAM_SUCCESS;
    }
    return status;
}

static PamStatus authenticate_user(const Options* options, const char* userId, const char* serviceName) {
    PamStatus status;
    AuthResponse* resp = http_auth_authenticate(options, &(AuthContext){userId, serviceName});
    if (resp->status == AUTH_AUTHORIZED) {
        status = PAM_SUCCESS;
    } else if (resp->status == AUTH_UNAUTHORIZED) {
        status = PAM_PERM_DENIED;
    } else if (resp->status == AUTH_ERROR) {
        status = PAM_AUTH_ERR;
        PAM_DEBUG("%s" ENDLINE, resp->errMsg);
    } else {
        status = PAM_AUTH_ERR;
    }
    free(resp);
    return status;
}

int pam_sm_authenticate(pam_handle_t *pamh, int flags,
                                   int argc, const char **argv) {
    const char* userName = NULL;
    const char* serviceName = NULL;
    char userId[12];  // Max 10 characters for 32bit value.
    
    PamStatus statusCode = get_service_name(pamh, &serviceName);
    if (statusCode == PAM_SUCCESS) {
        statusCode = get_user_name(pamh, &userName);
    }
    if (statusCode == PAM_SUCCESS) {
        statusCode = get_user_id(pamh, userName, userId);
    }
    if (statusCode == PAM_SUCCESS) {
        Options* options = options_parse(&(Args){argv, argc});
        statusCode = authenticate_user(options, userId, serviceName);
        options_free(options);
    }
    return statusCode;
}

int pam_sm_setcred(pam_handle_t *pamh, int flags,
			      int argc, const char **argv)
{
    return PAM_SUCCESS; /* Must return success for users of this service */
}