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

After successfully building the project with cmake, you can run the unit tests locally from the command line:

```cmd
cd build/tests && ./mu_tests
```

If you want to only print the overall test results, run the test executable like this:

```cmd
./mu_tests --gtest_brief=1
```

*note: test failures will still be reported individually if a test fails*

## Coverage

The code coverage can be generated using [gcov](https://gcc.gnu.org/onlinedocs/gcc/Gcov.html) and/or [llvm-cov](https://clang.llvm.org/docs/SourceBasedCodeCoverage.html)

A html coverage report can be found [TODO](https://github.com)

You can generate both coverage reports locally from the command line:

```cmd
cd coverage && ./coverage_gcov.sh
```

The coverage report will be generated in html form in a coverage/html folder. View the report by opening the index.html file inside that folder in a browser.
