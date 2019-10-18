#ifndef HTTP_AUTHENTICATE_H
#define HTTP_AUTHENTICATE_H

#include "pam-http/options.h"

#ifdef __cplusplus
extern "C" {
#endif
    
    /**
     * Which context the authentication request is for.
     */
    typedef struct {
        const char* userId;
        const char* serviceName;
    } AuthContext;

    /**
     * The response received from an authentication request.
     */
    typedef enum {
        AUTH_AUTHORIZED,
        AUTH_UNAUTHORIZED,
        AUTH_ERROR,
    } AuthResponseStatus;

    typedef struct {
        AuthResponseStatus status;
        const char* errMsg;
    } AuthResponse;

    /**
     * Send an authentication request.
     * 
     * @param options
     * @param ctx
     * @return auth response. Caller must free returned value after usage.
     */
    AuthResponse* http_auth_authenticate(const Options* options, const AuthContext* ctx);


#ifdef __cplusplus
}
#endif

#endif /* HTTP_AUTHENTICATE_H */

