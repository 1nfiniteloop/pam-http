FROM local/cpp-dev:latest

RUN apt-get update && \
    apt-get install \
        --no-install-recommends \
        --assume-yes \
        --quiet \
    openssh-server && \
    mkdir /var/run/sshd

# project dependencies
RUN apt-get install \
        --assume-yes \
        --quiet \
        --no-install-recommends \
    libstdc++-8-dev \
    libc6-dev \
    libcurl4 \
    libcurl4-openssl-dev \
    libpam0g-dev \
    libmicrohttpd-dev

# use as remote build host
EXPOSE 22
ENTRYPOINT ["/usr/sbin/sshd", "-D", "-e"]
