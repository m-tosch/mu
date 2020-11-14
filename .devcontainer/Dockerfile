FROM ubuntu:20.04

# add a non-root use with sudo access. Avoid permission issues with UID
# see https://aka.ms/vscode-remote/containers/non-root-user
ARG USERNAME=vscode
ARG USER_UID=1000
ARG USER_GID=$USER_UID

ENV TZ=Europe/Berlin
RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone

RUN apt-get update -y

## build
# gcc, make ...
RUN apt-get install -y build-essential
RUN apt-get install -y cmake
RUN apt-get install -y manpages-dev

## clang
# this installs llvm tools too
RUN apt-get install -y clang-9
RUN update-alternatives --install /usr/bin/clang clang /usr/bin/clang-9 100

## debuggig
RUN apt-get install -y gdb

## documentation
RUN apt-get install -y doxygen
RUN apt-get install -y graphviz

## version control
RUN apt-get install -y git

## coverage
# gcov already comes with gcc. gcc comes through build-essential. genhtml comes with lcov
RUN apt-get install -y lcov
RUN update-alternatives --install /usr/bin/llvm-cov llvm-cov /usr/bin/llvm-cov-9 100
RUN update-alternatives --install /usr/bin/llvm-profdata llvm-profdata /usr/bin/llvm-profdata-9 100

## python
# check if this is needed at all
# RUN apt-get install -y python 
RUN apt-get install -y python3.8
RUN apt-get -y install python3-pip

## formatting & linting
# clang language server
RUN apt-get install -y clangd-9
RUN update-alternatives --install /usr/bin/clangd clangd /usr/bin/clangd-9 100
# doesn't have to be v9 of clang. will install clang as a dependency
RUN apt-get install -y clang-format 
RUN apt-get install -y clang-tidy 
RUN pip3 install cpplint
# just for clang tidy to find the dependency to gtest
RUN apt-get install -y googletest
