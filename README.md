# <img src="https://render.githubusercontent.com/render/math?math=\Huge\mu" style="vertical-align:bottom">

A small, simple c++ math library

## Usage

TODO

## Installation

TODO

## Documentation

The documentation can be found [here](https://github.com) **TODO**

You can generate the documentation locally from the command line:

```cmd
cd doc && doxygen Doxyfile
```

The documentation will be generated in html form inside a  doc/html folder. View the report by opening the index.html file inside that folder in a browser.

## Tests

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

The coverage report can be found [here](https://github.com) **TODO**

You can generate a coverage report locally from the command line:

```cmd
cd coverage && ./coverage.sh
```

The coverage report will be generated in html form in a coverage/html folder. View the report by opening the index.html file inside that folder in a browser.
