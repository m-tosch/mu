# project root directory relative to the location of this script
ROOTDIR=".."
# working directory for intermediate coverage files
WORKDIR="$ROOTDIR/build/tests/CMakeFiles/mu_tests.dir"
# coverage directory for a /html report to be generated in
COVERAGEDIR="$ROOTDIR/coverage"

# 1. cmake build
# note: same command as in .vscode/tasks.json
mkdir -p $ROOTDIR/build && cd $ROOTDIR/build && CC=gcc CXX=g++ cmake .. -G "Unix Makefiles" && make
# 2. google test main exectuable. only print test failures (generate .gcda files)
# note: same command as in .vscode/tasks.json
$ROOTDIR/build/tests/mu_tests --gtest_brief=1
# 3. generate coverage .info (lcov uses gcov)
# exclude all external headers then include only the ones for this project
lcov -c --directory $WORKDIR --output-file $WORKDIR/main_coverage.info --no-external --directory $ROOTDIR/include --rc lcov_branch_coverage=1
# 4. generate html report
genhtml $WORKDIR/main_coverage.info --output-directory $COVERAGEDIR/html_gcov