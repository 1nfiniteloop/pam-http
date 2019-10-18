#ifndef HTTP_CLIENT_H
#define HTTP_CLIENT_H

#include <stddef.h>
#include <stdbool.h>

#define HTTP_RESP_OK            200
#define HTTP_RESP_UNAUTHORIZED  401

#ifdef __cplusplus
extern "C" {
#endif

    /**
     * Used for creating a POST-parameter string.
     */
    typedef struct {
        const char* key;
        const char* value;
    } HttpParameter;

    /**
     * Options provided for creating a session.
     */
    typedef struct {
        const char* key;
        const char* cert;
    } HttpClientCert;
    
    typedef struct {
        long timeout;
        const char* cacert;
        HttpClientCert clientCert;
    } HttpOptions;

    /**
     * HTTP Response returned from a HTTP request.
     */
    typedef struct {
        bool error;
        const char* msg;
    } HttpError;
    
    typedef struct {
        long responseCode;
        const char* body; /* Not used at the moment */
        HttpError err;
    } HttpResponse;
    
    typedef struct HttpSessionImpl HttpSession;
    
    /**
     * Create a new session.
     * 
     * @param options
     * @return session
     */
    HttpSession* http_client_new_session(HttpOptions* options);
    
    /**
     * Free resources held by session.
     * 
     * @param session
     */
    void http_client_free_session(HttpSession* session);
    
    /**
     * Build a parameter string to use e.g. when calling post(...).
     * 
     * @param session
     * @param parameters, copied.
     * @param len
     * @return encoded parameter string. Caller must free returned value after usage.
     */
    char* http_client_encode_parameters(HttpSession* session, const HttpParameter* parameters[], const size_t len);
    
    /**
     * Send a HTTP POST request.
     * 
     * @param session
     * @param url
     * @param parameters
     * @return http response. Caller must free returned value after usage.
     */
    HttpResponse* http_client_post(HttpSession* session, const char* url, const char* parameters);
    
    
#ifdef __cplusplus
}
#endif

#endif /* HTTP_CLIENT_H */

