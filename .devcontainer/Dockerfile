FROM ubuntu:bionic

ENV DEBIAN_FRONTEND=noninteractive

RUN sed --in-place=~ 's|archive.ubuntu.com|ftp.acc.umu.se|g' /etc/apt/sources.list

# base-tools for C and C++
RUN apt-get update \
    && apt-get install \
        --no-install-recommends \
        --assume-yes \
        --quiet \
        autoconf \
        automake \
        cmake \
        g++ \
        gcc \
        gdb \
        libtool \
        make \
        pkg-config \
    && rm -r /var/lib/apt/lists/*

# Other useful tools for C and C++
RUN apt-get update \
    && apt-get install \
        --no-install-recommends \
        --assume-yes \
        --quiet \
        cppcheck \
        valgrind \
    && rm -r /var/lib/apt/lists/*

# Other useful tools.
RUN apt-get update \
    && apt-get install \
        --no-install-recommends \
        --assume-yes \
        --quiet \
        ca-certificates \
        curl \
        git \
        less \
        nano \
        netcat \
        openssl \
        xz-utils \
    && rm -r /var/lib/apt/lists/*

# Project dependencies
RUN apt-get update \
    && apt-get install \
        --no-install-recommends \
        --assume-yes \
        --quiet \
        libstdc++-8-dev \
        libc6-dev \
        libcurl4 \
        libcurl4-openssl-dev \
        libpam0g-dev \
        libmicrohttpd-dev \
    && rm -r /var/lib/apt/lists/*

RUN useradd \
        --uid 1000 \
        --shell /bin/bash \
        --create-home \
        build

# Don't run as root inside container, 
# see https://github.com/microsoft/vscode-remote-release/issues/22
ENV HOME /home/build
USER build

CMD ["/bin/bash", "-l"]
