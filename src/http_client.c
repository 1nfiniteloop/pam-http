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

#include <curl/curl.h>
#include <stdlib.h>
#include <string.h>

#include "pam-http/http_client.h"


struct SessionImpl {
    CURL *curl;
};

/* Response body not used */
static size_t HttpResponseBodyCallback(void *contents, size_t size, size_t nmemb, void *userp) {
    return size * nmemb;
}

void setOptions(Session* session, HttpOptions* options) {
    if (options) {
        ClientCert* clientCert = &options->clientCert;
        if (clientCert->cert && clientCert->key) {
            curl_easy_setopt(session->curl, CURLOPT_SSLCERT, clientCert->cert);
            curl_easy_setopt(session->curl, CURLOPT_SSLKEY, clientCert->key);
            //curl_easy_setopt(session->curl, CURLOPT_SSL_VERIFYHOST, 0L); /* verify the certificate's name against host. TODO add option to disable? */
        }
        if (options->cacert) {
            curl_easy_setopt(session->curl, CURLOPT_CAINFO, options->cacert);
        }
        if (options->timeout) {
            curl_easy_setopt(session->curl, CURLOPT_TIMEOUT, options->timeout);
        }
    }
}

Session* newSession(HttpOptions* options) {
    Session* session = malloc(sizeof (Session));
    if (session) {
        session->curl = curl_easy_init();
        setOptions(session, options);        
    }
    return session;
}

void freeSession(Session* session) {
    if (session) {
        curl_easy_cleanup(session->curl);
        free(session);
    }
}

HttpResponse* post(Session* session, const char* url, const char* parameters) {
    HttpResponse* response = malloc(sizeof(HttpResponse));
    response->body = NULL; /* Not used at the moment */
    curl_easy_setopt(session->curl, CURLOPT_URL, url);
    curl_easy_setopt(session->curl, CURLOPT_WRITEFUNCTION, HttpResponseBodyCallback);
    curl_easy_setopt(session->curl, CURLOPT_POSTFIELDSIZE, (long) strlen(parameters));
    curl_easy_setopt(session->curl, CURLOPT_COPYPOSTFIELDS, parameters);
    CURLcode res = curl_easy_perform(session->curl);

    curl_easy_getinfo(session->curl, CURLINFO_RESPONSE_CODE, &response->responseCode);
    HttpError *error = &response->err;
    error->error = (res != CURLE_OK);
    error->msg = curl_easy_strerror(res);
    return response;
}

char* encodeParameter(Session *session, const Parameter* parameter) {
    char* keyEncoded = curl_easy_escape(session->curl, parameter->key, strlen(parameter->key));
    char* valueEncoded = curl_easy_escape(session->curl, parameter->value, strlen(parameter->value));
    size_t size = strlen(keyEncoded) + /* delimiterSize */ 1 + strlen(valueEncoded) + /* null-termination */ 1;
    char* parameterStr = calloc(size, sizeof(char));
    snprintf(parameterStr, size, "%s=%s", keyEncoded, valueEncoded);
    curl_free(keyEncoded);
    curl_free(valueEncoded);
    return parameterStr;
}

char* encodeParameters(Session* session, const Parameter* parameters[], const size_t len) {
    char* parameterStr = NULL;
    if (len) {
        const char* delimiter = "&";
        size_t totalSize = 0;
        char* encodedParameter[len];
        for (int i = 0; i < len; i++) {
            encodedParameter[i] = encodeParameter(session, parameters[i]);
            totalSize += strlen(encodedParameter[i]);
        }
        parameterStr = calloc((totalSize + /* no of delimiters */ (len - 1) + /* null-termination */ 1), sizeof (char));
        for (int i = 0; i < len; i++) {
            if (i > 0) {
                strncat(parameterStr, delimiter, strlen(delimiter));
            }
            strncat(parameterStr, encodedParameter[i], strlen(encodedParameter[i]));
            free(encodedParameter[i]);
        }        
    }
    return parameterStr;
}
