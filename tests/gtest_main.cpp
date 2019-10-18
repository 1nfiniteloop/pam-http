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