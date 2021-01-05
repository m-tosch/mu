# <font size="7"> μ </font>

[![](https://github.com/m-tosch/mu/workflows/cmake/badge.svg)](https://github.com/m-tosch/mu/actions?query=workflow%3ACMake)
[![](https://github.com/m-tosch/mu/workflows/doc/badge.svg)](https://m-tosch.github.io/mu/index.html)
[![codecov](https://codecov.io/gh/m-tosch/mu/branch/master/graph/badge.svg?token=K4O5W48EUX)](https://codecov.io/gh/m-tosch/mu)

A small, simple c++ math library

The goal of this repository is to provide a header library for fixed size vector and matrix math that is easy to use and fully verified by tests.

## Demo

### Example 1

Calculate the mean and standard deviation of a vector.

```cpp
mu::Vector<3,float> v = {8.3F, 1.9F, 4.5F};
float mean = v.mean();
float std = v.std();
std::cout << "mean: " << mean << std::endl;
std::cout << "std: " << std << std::endl;
```

output

```txt
mean: 4.9
std: 2.62805
```

### Example 2

Find the maximum value on a matrix diagonal.

<details>
<summary>code</summary>

```cpp
mu::Matrix<3,3,int> m = { {3,5,7}, {6,1,9}, {4,8,6} };
int max = mu::max(m.diag());
std::cout << m << std::endl;
std::cout << "max element on diagonal: " << max << std::endl;
```

output

```txt
[ [ 3, 5, 7 ],
  [ 6, 1, 9 ],
  [ 4, 8, 6 ] ]
max element on diagonal: 6
```

</details>

### Example 3

Rotate a 2D vector by π/2.

<details>
<summary>code</summary>

```cpp
mu::Vector2D<float> v = {2.25F, 5.75F};
std::cout << "before: " << v << std::endl;
v.rotate(mu::pi / 2);
std::cout << "after: " << v << std::endl;
```

output

```txt
before: [ 2.25, 5.75 ]
after: [ -5.75, 2.25 ]
```

</details>

### Example 4

Use references in a vector. (use carefully)

<details>
<summary>code</summary>

```cpp
int a = 3;
int b = 4;
mu::Vector<2, std::reference_wrapper<int>> v = {std::ref(a), std::ref(b)};
v[0].get() = 10;
std::cout << "v: " << v << std::endl;
std::cout << "a: " << a << " b: " << b << std::endl;
```

output

```txt
v: [ 10, 4 ]
a: 10 b: 4
```

</details>

## Usage

TODO

1. link with cmake
2. include header
```cpp
#include "mu/vector.h"
#include "mu/matrix.h"
```

## Installation

[Docker Desktop](https://www.docker.com/products/docker-desktop)

[Visual Studio Code](https://code.visualstudio.com/download)

Open the repository as a remote folder inside a container or clone it into a running linux volume in docker. The second options runs faster.

## Documentation

The documentation can be found [here](https://m-tosch.github.io/mu/index.html)

You can generate the documentation locally from the command line inside the `doc` folder:

```cmd
doxygen Doxyfile
```

The documentation will be generated in html form inside a `doc/html` folder. View the report by opening the `index.html` file inside that folder in a browser.

## Tests

The tests use [googletest](https://github.com/google/googletest)

After successfully building the project (with cmake), you can run the tests locally from the command line inside the generated `build/tests` folder:

```cmd
./mu_tests
```

## Coverage

The coverage can be found [here](https://codecov.io/gh/m-tosch/mu)

The code coverage can be generated using [gcov](https://gcc.gnu.org/onlinedocs/gcc/Gcov.html) or [llvm-cov](https://clang.llvm.org/docs/SourceBasedCodeCoverage.html). gcov uses the gcc compiler while llvm-cov uses clang. The latter was implemented to be able to inspect branch coverage or, the llvm equivalent, "region coverage".

You can generate both coverage reports locally from the command line inside the `coverage` folder:

For gcov (requires gcc)

```cmd
bash coverage_gcov.sh
```

For llvm-cov (requires clang)

```cmd
bash coverage_llvm.sh
```

The coverage report will be generated in html form in a `coverage/html_gcov` or a `coverage/html_llvm` folder respectively. View the report by opening the `index.html` file inside that folder in a browser.
