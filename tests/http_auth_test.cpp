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

#include "pam-http/http_auth.h"
#include "pam-http/http_client.h" /* HTTP_RESP_OK, HTTP_RESP_UNAUTHORIZED */

/**
 * Test with real HTTP request against http mock server.
 */
TEST(TestHttpAuth, TestAuthorized) {
    Options* options = new Options{};
    options->url = strdup("http://localhost:8080/api/auth");
    AuthContext ctx = {"valid user", "login"};
    HttpAuthResponse* resp = authenticate(options, &ctx);
    ASSERT_EQ(AUTH_AUTHORIZED, resp->status);
    ASSERT_STREQ("No error", resp->errMsg);
    free(resp);
    freeOptions(options);
}

TEST(TestHttpAuth, TestUnauthorized) {
    Options* options = new Options{};
    options->url = strdup("http://localhost:8080/api/auth");
    AuthContext ctx = {"unprivileged-user", "login"};
    HttpAuthResponse* resp = authenticate(options, &ctx);
    ASSERT_EQ(AUTH_UNAUTHORIZED, resp->status);
    ASSERT_STREQ("No error", resp->errMsg);
    free(resp);
    freeOptions(options);
}

TEST(TestHttpAuth, TestUrlError) {
    Options* options = new Options{};
    options->url = strdup("http://localhost:1234");
    AuthContext ctx = {"unprivileged-user", "login"};
    HttpAuthResponse* resp = authenticate(options, &ctx);
    ASSERT_EQ(AUTH_ERROR, resp->status);
    ASSERT_STRNE("No error", resp->errMsg);
    free(resp);
    freeOptions(options);
}

TEST(TestHttpAuth, TestErrorResponseOnUnexpectedStatusCode) {
    Options* options = new Options{};
    options->url = strdup("http://localhost:8080/api"); /* server returns 400 bad request */
    AuthContext ctx = {"some-user", "login"};
    HttpAuthResponse* resp = authenticate(options, &ctx);
    ASSERT_EQ(AUTH_ERROR, resp->status);
    ASSERT_STRNE("No error", resp->errMsg);
    free(resp);
    freeOptions(options);
}
