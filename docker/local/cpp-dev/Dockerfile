FROM ubuntu:bionic

# base-tools.
RUN apt-get update && \
    apt-get install \
        --no-install-recommends \
        --assume-yes \
        --quiet \
    gcc \
    g++ \
    gdb \
    make \
    cmake \
    cppcheck \
    valgrind

# utilities
RUN apt-get install \
        --no-install-recommends \
        --assume-yes \
        --quiet \
    less \
    nano \
    ca-certificates \
    curl \
    netcat

RUN useradd \
        --uid 1000 \
        --shell /bin/bash \
        --create-home \
        build && \
    echo "build:build" | chpasswd

CMD ["/bin/bash", "-l"]
