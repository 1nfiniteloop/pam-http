#include <gtest/gtest.h>
#include "pam-http/options.h"


class OptionsTest : public ::testing::Test {
    protected:
        //OptionsTest() = default;
        void SetUp() override {
            opt = nullptr;
        }
        
        void TearDown() override {
            options_free(opt);
        }
        Options* opt = nullptr;
        Args args = {};
        Options defaultOptions = {30 /* Default timeout */};
};

/**
 * Test argument input.
 */
TEST_F(OptionsTest, TestEmptyOptions) {
    opt = options_parse(&args);
    ASSERT_TRUE(memcmp(&defaultOptions, opt, sizeof(Options)) == 0) << "Expecting an empty struct with default values";
}

TEST_F(OptionsTest, TestUnknownOption) {
    const char* unknown[] = {"some=value"};
    args.arg = unknown;
    args.size = 1;
    opt = options_parse(&args);
    ASSERT_TRUE(memcmp(&defaultOptions, opt, sizeof(Options)) == 0) << "Expecting an empty struct with default values";
}

TEST_F(OptionsTest, TestOptionWithoutValue) {
    const char* url[] = {"url"};
    args.arg = url;
    args.size = 1;
    opt = options_parse(&args);
    ASSERT_EQ(NULL, opt->url);
}

/**
 * Tests on content of struct "Options"
 */
TEST_F(OptionsTest, TestTimeout) {
    constexpr long expectedTimeout = 4;
    const char* timeout[] = {"timeout=4"};
    args.arg = timeout;
    args.size = 1;
    opt = options_parse(&args);
    ASSERT_EQ(expectedTimeout, opt->timeout);
}

TEST_F(OptionsTest, TestDefaultTimeout) {
    opt = options_parse(&args);
    ASSERT_EQ(OPT_DEFAULT_TIMEOUT, opt->timeout);
}

TEST_F(OptionsTest, TestInvalidTimeoutValue) {
    const char* timeout[] = {"timeout=junk"};
    args.arg = timeout;
    args.size = 1;
    opt = options_parse(&args);
    ASSERT_EQ(0L, opt->timeout); /* can't decide if value is just junk or "0" during conversion, see "atol" */
}

TEST_F(OptionsTest, TestUrl) {
    const char* url[] = {"url=http://example.com"};
    args.arg = url;
    args.size = 1;
    opt = options_parse(&args);
    ASSERT_STREQ("http://example.com", opt->url);
}

TEST_F(OptionsTest, TestCaCert) {
    const char* cacert[] = {"cacert=/etc/ssl/cacert.pem"};
    args.arg = cacert;
    args.size = 1;
    opt = options_parse(&args);
    ASSERT_STREQ("/etc/ssl/cacert.pem", opt->cacert);
}

TEST_F(OptionsTest, TestCaCertAndCertPathWithoutTrailingSlash) {
    const char* cacert[] = {"cacert=cacert.pem", "cert-path=/etc/ssl"};
    args.arg = cacert;
    args.size = 2;
    opt = options_parse(&args);
    ASSERT_STREQ("/etc/ssl/cacert.pem", opt->cacert);
}

TEST_F(OptionsTest, TestCaCertAndCertPathWithTrailingSlash) {
    const char* cacert[] = {"cacert=cacert.pem", "cert-path=/etc/ssl/"};
    args.arg = cacert;
    args.size = 2;
    opt = options_parse(&args);
    ASSERT_STREQ("/etc/ssl/cacert.pem", opt->cacert);
}

TEST_F(OptionsTest, TestCert) {
    const char* cert[] = {"cert=/etc/ssl/cert.pem"};
    args.arg = cert;
    args.size = 1;
    opt = options_parse(&args);
    ASSERT_STREQ("/etc/ssl/cert.pem", opt->cert);
}

TEST_F(OptionsTest, TestCertWithCertPath) {
    const char* cert[] = {"cert=cert.pem", "cert-path=/etc/ssl/"};
    args.arg = cert;
    args.size = 2;
    opt = options_parse(&args);
    ASSERT_STREQ("/etc/ssl/cert.pem", opt->cert);
}

TEST_F(OptionsTest, TestKey) {
    const char* key[] = {"key=/etc/ssl/key.pem"};
    args.arg = key;
    args.size = 1;
    opt = options_parse(&args);
    ASSERT_STREQ("/etc/ssl/key.pem", opt->key);
}

TEST_F(OptionsTest, TestKeyWithCertPath) {
    const size_t len = 2;
    const char* key[len] = {"cert-path=/etc/ssl", "key=client.cert.pem"};
    args.arg = key;
    args.size = len;
    opt = options_parse(&args);
    ASSERT_STREQ("/etc/ssl/client.cert.pem", opt->key);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
