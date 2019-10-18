#include <gtest/gtest.h>

#include "pam-http/http_client.h"


TEST(TestHttpClient, TestEncodeParametersNone) {
    HttpSession* session = http_client_new_session(NULL);
    constexpr size_t size = 0;    
    char* parameterStr = http_client_encode_parameters(session, NULL, size);
    ASSERT_EQ(NULL, parameterStr);
    free(parameterStr);
    http_client_free_session(session);
}

TEST(TestHttpClient, TestEncodeParametersMultiple) {
    HttpOptions* opt = NULL;
    HttpSession* session = http_client_new_session(opt);

    constexpr size_t size = 3;
    const HttpParameter* parameters[size];
    HttpParameter firstParam = {"a", "1"};
    HttpParameter secondParam = {"b", "2"};
    HttpParameter thirdParam = {"c", "3"};
    parameters[0] = &firstParam;
    parameters[1] = &secondParam;
    parameters[2] = &thirdParam;
    
    char* parameterStr = http_client_encode_parameters(session, parameters, size);
    ASSERT_STREQ("a=1&b=2&c=3", parameterStr);
    free(parameterStr);
    http_client_free_session(session);
}

/**
 * Test with real HTTP request sent.
 */
TEST(TestHttpClient, TestErrorResponseOnFaultyUrl) {
    HttpOptions* opt = NULL;
    HttpSession* session = http_client_new_session(opt);
    HttpResponse* resp = http_client_post(session, "http://void:8080/api/auth", "post data");
    ASSERT_TRUE(resp->err.error);
    free(resp);
    http_client_free_session(session);
}

TEST(TestHttpClient, TestResponseCodeOnSuccessfulHttpPost) {
    HttpOptions* opt = NULL;
    HttpSession* session = http_client_new_session(opt);
    HttpResponse* resp = http_client_post(session, "http://localhost:8080/api/auth", "user=valid%20user&service=login");
    ASSERT_EQ(HTTP_RESP_OK, resp->responseCode) << "error: " << resp->err.msg << std::endl;
    free(resp);
    http_client_free_session(session);
}

TEST(TestHttpClient, TestErrorResponseOnSuccessfulHttpPost) {
    HttpOptions* opt = NULL;
    HttpSession* session = http_client_new_session(opt);
    HttpResponse* resp = http_client_post(session, "http://localhost:8080/api/auth", "user=valid%20user&service=login");
    ASSERT_FALSE(resp->err.error);
    free(resp);
    http_client_free_session(session);
}
