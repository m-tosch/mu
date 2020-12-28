#!/bin/bash

# project root directory relative to the location of this script
ROOTDIR="$PWD/.."
# working directory for intermediate coverage files
WORKDIR="$ROOTDIR/build/tests/CMakeFiles/mu_tests.dir"
# coverage directory for a /html report to be generated in
COVERAGEDIR="$ROOTDIR/coverage"

# 1. cmake build
# note: same command as in .vscode/tasks.json
mkdir -p $ROOTDIR/build && cd $ROOTDIR/build && CC=gcc CXX=g++ cmake .. -G "Unix Makefiles" && cmake --build . -- -j8
# 2. google test main exectuable. only print test failures (generate .gcda files)
# note: same command as in .vscode/tasks.json
$ROOTDIR/build/tests/mu_tests --gtest_brief=1
# 3. generate xml gcovr report. include only the "include" folder for coverage
mkdir -p $COVERAGEDIR/xml_gcovr
cd $WORKDIR && gcovr -r $ROOTDIR/.. -f ../../../../include --xml -o $COVERAGEDIR/xml_gcovr/index.xml
