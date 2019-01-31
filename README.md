## Description

Linux-pam (Pluggable Authentication Modules) is responsible for handling authentication requests in a flexible way from linux applications, such as login. This is a minimal pam-module implementation written in C which performs authentication through HTTP.

The purpose for developing this pam-module is to delegate the authentication procedure to a remote party, and keep options open of how authentication actually is performed. Compare with options like kerberos, ldap, pam_*sql, which is both higly coupled to a specific implemetation and complicated to install & configure.

By using a simple HTTP POST request we allow the remote party (authentication server) to decide wether to use ldap, sql-database, or even omit local password prompting for other authentication schemes such as Oauth2, OpenID, BankID. A mutual trust between server and pam-client is establish using ssl server & client certificates.

## Build & install

1. Install required packages `libcurl4`, `libcurl4-openssl-dev` and `libpam0g-dev` (on Ubuntu).
2. Build libpam with `make CONF=release all`
3. Copy the `pam-http/dist/Release/GNU-Linux/libpam-http.so` into `/lib/x86_64-linux-gnu/security` (on Ubuntu).

## Configuration

Each Linux utility which need authentication and uses pam have a configuration file in `/etc/pam.d`. Example `su` has its own configuration file named accordingly, same as for `login`, `sudo`, `passwd` etc. A pam-module consists of four different services; auth, session, account, password which always is present in each configuration file. See more @ http://www.linux-pam.org/Linux-PAM-html/sag-configuration-file.html

This module implements only the *auth* service, this is the only service you need to reconfigure. Below is an example for `/etc/pam.d/login`. You might place the pam-http configuration just above the common-auth include.

```conf
...
# Custom http authentication
auth     [success=done perm_denied=die new_authtok_reqd=done default=ignore]     libpam-http.so url=https://auth-server.com:443/api/auth cert-path=/etc/pam-http.d/ssl key=client.key.pem cert=client.cert.pem cacert=ca-chain.cert.pem

# Standard Un*x authentication.
@include common-auth

...
```

The options within the brackets above means:

* A successfull auth request will return success to the application, without calling any further modules in the stack by using `success=done`.
* Errors such as connectivity issues, outdated certificateallows fallback to unix passwd authentication by using `default=ignore`.
* Until here it's equivalent to use *sufficient*. The difference here is `perm_denied=die` which stops evaluation of further modules in the pam-stack when "401 - Permission Denied" is returned from the auth-server.


Available command-line options in format "key=value" are:

* **timeout=**    *optional, default 30s* - Max timeout for a http request.
* **url=**        *required* - Url endpoint used for authentication.
* **cert-path=**  *optional* - Prefix path for certificate files below.
* **cacert=**     *optional* - Bundled certificate chain with intermediate and root certificate used to validate server certificate.
* **key=, cert=** *optional* - Client certificate.

## API

The authentication is performed by sending a http POST request to a server with parameters for username and service-name (e.g. login, sudo, su). Password is not part of the http post request since my intention with this project is to avoid the need for local user password promting. 

The server can choose to send a 200 status code for grant authentication or 401 for deny. Other status codes are treated as errors. The pam-http module make sure that user exists locally before sending a request.

## Develop

The project is built with Netbeans IDE, using a docker-container as remote build host. See Dockerfile for setting up a complete development environment. Tests is written in C++ for conveniece and have further dependencies located as git submodules under folder `external/`.

To get tests running you need to build the libraries gtest and httpmockserver under `external/` and install package `libmicrohttpd-dev` which the http mock server uses.

## Reference

Some sources of inspiration used within this project:

* http://www.linux-pam.org/Linux-PAM-html/
* https://github.com/linux-pam/linux-pam/
* https://fedetask.com/write-linux-pam-module/
* https://github.com/gmjosack/nss_http

