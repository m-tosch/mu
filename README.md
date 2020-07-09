# <font size="7"> μ </font>

A small, simple c++ math library

## Usage

TODO

## Installation

TODO

## Documentation

The documentation can be found [TODO](https://github.com)

You can generate the documentation locally from the command line:

```cmd
cd doc && doxygen Doxyfile
```

The documentation will be generated in html form inside a  doc/html folder. View the report by opening the index.html file inside that folder in a browser.

## Tests

The unit tests are written using [googletest](https://github.com/google/googletest)

After successfully building the project (with cmake), you can run the unit tests locally from the command line:

```cmd
cd build/tests && ./mu_tests
```

If you want to only print the overall test results, run the test executable like this:

```cmd
./mu_tests --gtest_brief=1
```

*note: individual test failures will still be reported if a test fails*

## Coverage

The coverage can be found [TODO](https://github.com)

The code coverage can be generated using [gcov](https://gcc.gnu.org/onlinedocs/gcc/Gcov.html) or [llvm-cov](https://clang.llvm.org/docs/SourceBasedCodeCoverage.html). gcov uses the gcc compiler while llvm-cov uses clang. The latter was implemented to be able to inspect branch coverage through what llvm calls "region coverage". gcov can only provide basic line coverage.

You can generate both coverage reports locally from the command line:

For gcov (requires gcc)

```cmd
cd coverage && ./coverage_gcov.sh
```

For llvm-cov (requires clang)

```cmd
cd coverage && ./coverage_llvm.sh
```

The coverage report will be generated in html form in a coverage/html_gcov or a coverage/html_llvm folder respectively. View the report by opening the index.html file inside that folder in a browser.
