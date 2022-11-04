FROM ubuntu:latest

WORKDIR /home
COPY . .

RUN apt-get -y update; \
    apt-get -y install apt-utils \
    g++ libgtest-dev googletest \
    valgrind build-essential make

RUN make build && make valgrind
