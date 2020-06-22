# project root directory relative to the location of this file
ROOTDIR=".."
# working directory for intermediate coverage files
WORKDIR="$ROOTDIR/build/tests/CMakeFiles/mu_tests.dir"

# 1. cmake build
# note: same command as in .vscode/tasks.json
mkdir -p $ROOTDIR/build && cd $ROOTDIR/build && cmake .. -G \"Unix Makefiles\" && make
# 2. google test main exectuable. only print test failures (generate .gcda files)
# note: same command as in .vscode/tasks.json
$ROOTDIR/build/tests/mu_tests --gtest_brief=1
# 3. generate coverage .info (lcov uses gcov)
# exclude all external headers then include only the ones for this project
lcov --directory $WORKDIR --capture --output-file $WORKDIR/main_coverage.info --no-external --directory $ROOTDIR/include
# 4. generate html report
genhtml $WORKDIR/main_coverage.info --output-directory html