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

#include <gtest/gtest.h>

#include "pam-http/http_client.h"


TEST(TestHttpClient, TestEncodeParametersNone) {
    Session* session = newSession(NULL);
    constexpr size_t size = 0;    
    char* parameterStr = encodeParameters(session, NULL, size);
    ASSERT_EQ(NULL, parameterStr);
    free(parameterStr);
    freeSession(session);
}

TEST(TestHttpClient, TestEncodeParametersMultiple) {
    HttpOptions* opt = NULL;
    Session* session = newSession(opt);

    constexpr size_t size = 3;
    const Parameter* parameters[size];
    Parameter firstParam = {"a", "1"};
    Parameter secondParam = {"b", "2"};
    Parameter thirdParam = {"c", "3"};
    parameters[0] = &firstParam;
    parameters[1] = &secondParam;
    parameters[2] = &thirdParam;
    
    char* parameterStr = encodeParameters(session, parameters, size);
    ASSERT_STREQ("a=1&b=2&c=3", parameterStr);
    free(parameterStr);
    freeSession(session);
}

/**
 * Test with real HTTP request sent.
 */
TEST(TestHttpClient, TestErrorResponseOnFaultyUrl) {
    HttpOptions* opt = NULL;
    Session* session = newSession(opt);
    HttpResponse* resp = post(session, "http://void:8080/api/auth", "post data");
    ASSERT_TRUE(resp->err.error);
    free(resp);
    freeSession(session);
}

TEST(TestHttpClient, TestResponseCodeOnSuccessfulHttpPost) {
    HttpOptions* opt = NULL;
    Session* session = newSession(opt);
    HttpResponse* resp = post(session, "http://localhost:8080/api/auth", "user=valid%20user&service=login");
    ASSERT_EQ(HTTP_RESP_OK, resp->responseCode) << "error: " << resp->err.msg << std::endl;
    free(resp);
    freeSession(session);
}

TEST(TestHttpClient, TestErrorResponseOnSuccessfulHttpPost) {
    HttpOptions* opt = NULL;
    Session* session = newSession(opt);
    HttpResponse* resp = post(session, "http://localhost:8080/api/auth", "user=valid%20user&service=login");
    ASSERT_FALSE(resp->err.error);
    free(resp);
    freeSession(session);
}
