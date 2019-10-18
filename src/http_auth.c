#include <stdlib.h>

#include "pam-http/http_auth.h"
#include "pam-http/http_client.h"


static char* create_http_parameters(HttpSession* session, const AuthContext* ctx) {
    const size_t size = 2;
    const HttpParameter *parameters[size];
    parameters[0] = &(HttpParameter){"unix_account_id", ctx->userId};
    parameters[1] = &(HttpParameter){"service", ctx->serviceName};
    return http_client_encode_parameters(session, parameters, size);
}

static HttpOptions* create_http_options(const Options* options) {
    HttpOptions* httpOptions = malloc(sizeof(HttpOptions));
    httpOptions->timeout = options->timeout;
    httpOptions->cacert = options->cacert;
    httpOptions->clientCert.cert = options->cert;
    httpOptions->clientCert.key = options->key;
    return httpOptions;
}

static AuthResponse* send_http_auth_request(HttpSession* session, const char* url, const char* parameters) {
    AuthResponse* authResponse = malloc(sizeof(AuthResponse));
    HttpResponse* resp = http_client_post(session, url, parameters);
        if (resp->err.error) {
            authResponse->status = AUTH_ERROR;
            authResponse->errMsg = resp->err.msg;       /* Unsuccessful request */
        } else {
            if (resp->responseCode == HTTP_RESP_OK) {
                authResponse->status = AUTH_AUTHORIZED;
                authResponse->errMsg = resp->err.msg;   /* Contains "No error" on successful request */
            } else if (resp->responseCode == HTTP_RESP_UNAUTHORIZED) {
                authResponse->status = AUTH_UNAUTHORIZED;
                authResponse->errMsg = resp->err.msg;   /* Contains "No error" on successful request */
            } else {
                authResponse->status = AUTH_ERROR;
                authResponse->errMsg = "Bad HTTP response code";
            }
        }
    free(resp);
    return authResponse;
}

AuthResponse* http_auth_authenticate(const Options* options, const AuthContext* ctx) {
    HttpOptions* httpOptions = create_http_options(options);
    HttpSession* session = http_client_new_session(httpOptions);
    char* parameters = create_http_parameters(session, ctx);
    AuthResponse* authResponse = send_http_auth_request(session, options->url, parameters);
    free(parameters);
    http_client_free_session(session);
    free(httpOptions);
    return authResponse;
}