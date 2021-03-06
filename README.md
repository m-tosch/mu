# <font size="7"> μ </font>

[![](https://github.com/m-tosch/mu/workflows/build/badge.svg)](https://github.com/m-tosch/mu/actions?query=workflow%3Abuild)
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

## Usage

To use this code with cmake, include the source directory either directly or into your target.

```cmake
target_include_directories(my_target PRIVATE ${CMAKE_SOURCE_DIR}/mu/include)
```

Afterwards, mu header files can be included like this

```cpp
#include "mu/vector.h"
```

<details>
<summary>minmal example</summary>

structure

```txt
/dependencies
  /mu
CMakeLists.txt
main.cpp
```

`CMakeLists.txt`

```cmake
cmake_minimum_required(VERSION 2.4)

project(hello_world)

add_executable(app main.cpp)

target_include_directories(app PRIVATE ${CMAKE_SOURCE_DIR}/dependencies/mu/include)
```

`main.cpp`
```cpp
#include <iostream>
#include "mu/vector.h"

int main() {
    mu::Vector<2,int> v = {1,2};
    std::cout << v << std::endl;
    return 0;
}
```

commands
```cmd
$ mkdir dependencies
$ cd dependencies
$ git clone https://github.com/m-tosch/mu.git
$ cd ..
$ mkdir build
$ cd build
$ cmake .
$ make
$ ./app
```

output
```txt
[ 1, 2 ]
```

</details>

## Installation

*\*for developers*

Tools

- [Docker Desktop](https://www.docker.com/products/docker-desktop)
  - [Ubuntu 20.04 LTS](https://www.microsoft.com/en-us/p/ubuntu-2004-lts/9n6svws3rx71) (Windows 10)
- [Visual Studio Code](https://code.visualstudio.com/download)
  - [Remote - Containers extension](https://marketplace.visualstudio.com/items?itemName=ms-vscode-remote.remote-containers)

In Docker Desktop settings under "WSL Integration" you should see the Ubuntu distro you just installed. Enable it then restart docker.

In VS code, clone the repository into a container: View → Command Palette... → "Remote-Containers: Clone Repository in Container Volume" or open the repository as a remote folder inside a container. The second option runs slower because of the constant communication with the host filesystem.

The `.devcontainer` folder holds files that specify all additional Software required for development. It is automatically installed when running the container for the first time.

## Documentation

The documentation can be found [here](https://m-tosch.github.io/mu/index.html)

You can generate the documentation locally from the command line inside the `doc` folder:

```cmd
doxygen Doxyfile
```

The documentation will be generated in html form inside a `doc/html` folder. View the report by opening the `index.html` file inside that folder in a browser.

## Tests

The tests use [googletest](https://github.com/google/googletest)

After successfully building the project, you can run the tests locally from the command line inside the generated `build/tests` folder:

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
