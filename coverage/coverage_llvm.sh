#!/bin/bash

# project root directory relative to the location of this script
ROOTDIR="$PWD/.."
# working directory for intermediate coverage files
WORKDIR="$ROOTDIR/build/tests"
# coverage directory for a /html report to be generated in
COVERAGEDIR="$ROOTDIR/coverage"

# 1. cmake build with clang
mkdir -p $ROOTDIR/build && cd $ROOTDIR/build && CC=clang CXX=clang++ cmake .. -G "Unix Makefiles" && cmake --build . -- -j8
# 2. run test executables. write raw profile
LLVM_PROFILE_FILE="$WORKDIR/mu_tests.profraw" $WORKDIR/mu_tests --gtest_brief=1
# 3. "Raw profiles have to be indexed before they can be used to generate coverage reports"
llvm-profdata merge -sparse $WORKDIR/mu_tests.profraw -o $WORKDIR/mu_tests.profdata
# 4. generate html report. exclude some folders from the coverage
llvm-cov show -format="text" $WORKDIR/mu_tests -instr-profile=$WORKDIR/mu_tests.profdata -output-dir="$COVERAGEDIR/text_llvm" \
--show-line-counts-or-regions -Xdemangler c++filt \
-ignore-filename-regex="coverage/*" -ignore-filename-regex="dependencies/*" -ignore-filename-regex="tests/*" 
