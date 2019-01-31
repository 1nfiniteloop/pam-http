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
#include <string>
#include <httpmockserver/mock_server.h>
#include <httpmockserver/test_environment.h>

#include "pam-http/http_client.h" /* HTTP_RESP_OK, HTTP_RESP_UNAUTHORIZED */

constexpr int server_port = 8080;

class HTTPMock : public httpmock::MockServer {
public:

    explicit HTTPMock(int port = server_port) : MockServer(port) {
    }
private:

    Response responseHandler(
            const std::string &url,
            const std::string &method,
            const std::string &data,
            const std::vector<UrlArg> &urlArguments,
            const std::vector<Header> &headers) {
        
        Response response{};
        if (method == "POST" && matchesPrefix(url, "/api/auth")) {
            if (authenticate(data)) {
                response = Response(HTTP_RESP_OK, "Fake HTTP response");
            } else {
                response = Response(HTTP_RESP_UNAUTHORIZED, "Unauthorized");
            }
        } else {
            response = Response(400, "Bad request");
        }
        return response;
    }

    bool authenticate(const std::string &data) {
        return data == "user=valid%20user&service=login";
    }
    
    bool matchesPrefix(const std::string &url, const std::string &str) const {
        return url.substr(0, str.size()) == str;
    }
};


int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    ::testing::AddGlobalTestEnvironment(new httpmock::TestEnvironment<HTTPMock>());
    return RUN_ALL_TESTS();
}