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

#include <stdlib.h>

#include "pam-http/http_auth.h"
#include "pam-http/http_client.h"


char* createHttpParameters(Session* session, const AuthContext* ctx) {
    const size_t size = 2;
    const Parameter *parameters[size];
    parameters[0] = &(Parameter){"user", ctx->userName};
    parameters[1] = &(Parameter){"service", ctx->serviceName};
    return encodeParameters(session, parameters, size);
}

HttpOptions* createHttpOptions(const Options* options) {
    HttpOptions* httpOptions = malloc(sizeof(HttpOptions));
    httpOptions->timeout = options->timeout;
    httpOptions->cacert = options->cacert;
    httpOptions->clientCert.cert = options->cert;
    httpOptions->clientCert.key = options->key;
    return httpOptions;
}

HttpAuthResponse* sendHttpAuthRequest(Session* session, const char* url, const char* parameters) {
    HttpAuthResponse* authResponse = malloc(sizeof(HttpAuthResponse));
    HttpResponse* resp = post(session, url, parameters);
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

HttpAuthResponse* authenticate(const Options* options, const AuthContext* ctx) {
    HttpOptions* httpOptions = createHttpOptions(options);
    Session* session = newSession(httpOptions);
    char* parameters = createHttpParameters(session, ctx);
    HttpAuthResponse* authResponse = sendHttpAuthRequest(session, options->url, parameters);
    free(parameters);
    freeSession(session);
    free(httpOptions);
    return authResponse;
}