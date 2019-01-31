/*
 * The MIT License
 *
 * Copyright 2019 Lars Gunnarsson.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
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


PamStatus getServiceName(pam_handle_t *pamh, const char** serviceName) {
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

PamStatus getUserName(pam_handle_t *pamh, const char** userName) {
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

PamStatus userExists(pam_handle_t *pamh, const char* username) {
    PamStatus status;
    struct passwd *pw = pam_modutil_getpwnam(pamh, username);
    if (pw == NULL) {
        status = PAM_USER_UNKNOWN;
        PAM_DEBUG("User %s does not exist" ENDLINE, username);
    } else {
        status = PAM_SUCCESS;
    }
    return status;
}

PamStatus authenticateUser(const Options* options, const char* userName, const char* serviceName) {
    PamStatus status;
    HttpAuthResponse* resp = authenticate(options, &(AuthContext){userName, serviceName});
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
    const char* userName;
    const char* serviceName;
    
    PamStatus statusCode = getServiceName(pamh, &serviceName);
    if (statusCode == PAM_SUCCESS) {
        statusCode = getUserName(pamh, &userName);
    }
    if (statusCode == PAM_SUCCESS) {
        statusCode = userExists(pamh, userName);
    }
    if (statusCode == PAM_SUCCESS) {
        Options* options = parseOptions(&(Args){argv, argc});
        statusCode = authenticateUser(options, userName, serviceName);
        freeOptions(options);
    }
    return statusCode;
}

int pam_sm_setcred(pam_handle_t *pamh, int flags,
			      int argc, const char **argv)
{
    return PAM_SUCCESS; /* Must return success for users of this service */
}