# Coverage

Coverage can be generated using either gcc or clang. The two main scripts in this repository are named accordingly

- coverage_gcov.sh
- coverage_llvm.sh

Additionally, there is a script that uses [gcovr](https://github.com/gcovr/gcovr) to generate the coverage via gcov and output the results in xml format. It is used for the CI/CD coverage generation which can be found in `.github/workflows`

- coverage_gcovr.sh

The explicit instantiations for template classes/functions can be found here, because they guarantee accurate coverage information.

- explicit.cpp
