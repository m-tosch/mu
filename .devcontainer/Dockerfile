FROM ubuntu:20.04

ENV TZ=Europe/Berlin
RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone

RUN apt-get update -y

## build
# gcc, make ...
RUN apt-get install -y build-essential
RUN apt-get install -y cmake
RUN apt-get install -y manpages-dev

## clang
RUN apt-get install -y clang

## debuggig
RUN apt-get install -y gdb

## documentation
RUN apt-get install -y doxygen
RUN apt-get install -y graphviz

## version control
RUN apt-get install -y git
# gpg sign commits. this allows key sharing between host and container
RUN apt-get install gnupg2 -y

## coverage
# gcov already comes with gcc. gcc comes through build-essential. genhtml comes with lcov
RUN apt-get install -y lcov
# llvm-cov (and llvm-profdata) are needed
RUN apt-get install -y llvm

## python
RUN apt-get install -y python3.8
RUN apt-get -y install python3-pip

## formatting & linting
# clang language server
RUN apt-get install -y clangd
# format & tidy
RUN apt-get install -y clang-format 
RUN apt-get install -y clang-tidy 
# cpplint
RUN pip3 install cpplint

# just for clang tidy to find the dependency to gtest
RUN apt-get install -y googletest
