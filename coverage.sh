# run prior to this script:
# 01. build with cmake
# 02. google test main exectuable (generate .gcda files)

WORKDIR="build/tests/CMakeFiles/mu_tests.dir"
# 1. generate coverage .info (lcov uses gcov)
# exclude all external headers then include only the ones for this project
lcov --directory $WORKDIR --capture --output-file $WORKDIR/main_coverage.info --no-external --directory ./include
# 2. generate html report
genhtml $WORKDIR/main_coverage.info --output-directory coverage
