#ifndef MU_UTILITY_H_
#define MU_UTILITY_H_

#include <cmath>
#include <type_traits>

namespace mu {

template <typename T>
typename std::enable_if<std::is_floating_point<T>::value, T>::type sin(
    T value) {
  return std::sin(value);
}

}  // namespace mu

#endif  // MU_UTILITY_H_