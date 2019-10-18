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
    AuthResponse* resp = http_auth_authenticate(options, &ctx);
    ASSERT_EQ(AUTH_AUTHORIZED, resp->status);
    ASSERT_STREQ("No error", resp->errMsg);
    free(resp);
    options_free(options);
}

TEST(TestHttpAuth, TestUnauthorized) {
    Options* options = new Options{};
    options->url = strdup("http://localhost:8080/api/auth");
    AuthContext ctx = {"unprivileged-user", "login"};
    AuthResponse* resp = http_auth_authenticate(options, &ctx);
    ASSERT_EQ(AUTH_UNAUTHORIZED, resp->status);
    ASSERT_STREQ("No error", resp->errMsg);
    free(resp);
    options_free(options);
}

TEST(TestHttpAuth, TestUrlError) {
    Options* options = new Options{};
    options->url = strdup("http://localhost:1234");
    AuthContext ctx = {"unprivileged-user", "login"};
    AuthResponse* resp = http_auth_authenticate(options, &ctx);
    ASSERT_EQ(AUTH_ERROR, resp->status);
    ASSERT_STRNE("No error", resp->errMsg);
    free(resp);
    options_free(options);
}

TEST(TestHttpAuth, TestErrorResponseOnUnexpectedStatusCode) {
    Options* options = new Options{};
    options->url = strdup("http://localhost:8080/api"); /* server returns 400 bad request */
    AuthContext ctx = {"some-user", "login"};
    AuthResponse* resp = http_auth_authenticate(options, &ctx);
    ASSERT_EQ(AUTH_ERROR, resp->status);
    ASSERT_STRNE("No error", resp->errMsg);
    free(resp);
    options_free(options);
}
