#ifndef MU_UTILITY_H_
#define MU_UTILITY_H_

#include <cmath>
#include <type_traits>

namespace mu {

/**
 * @brief sine
 *
 * computes the sine of the input value in radians
 *
 * @tparam T floating point type
 * @param value
 * @return std::enable_if<std::is_floating_point<T>::value, T>::type
 */
template <typename T>
typename std::enable_if<std::is_floating_point<T>::value, T>::type sin(
    T value) {
  return std::sin(value);
}

/**
 * @brief cosine
 *
 * computes the cosine of the input value in radians
 *
 * @tparam T floating point type
 * @param value
 * @return std::enable_if<std::is_floating_point<T>::value, T>::type
 */
template <typename T>
typename std::enable_if<std::is_floating_point<T>::value, T>::type cos(
    T value) {
  return std::cos(value);
}

/**
 * @brief tangens
 *
 * computes the tangens of the input value in radians
 *
 * @tparam T floating point type
 * @param value
 * @return std::enable_if<std::is_floating_point<T>::value, T>::type
 */
template <typename T>
typename std::enable_if<std::is_floating_point<T>::value, T>::type tan(
    T value) {
  return std::tan(value);
}

/**
 * @brief arc sine
 *
 * computes the arc sine of the input value in radians
 *
 * @tparam T floating point type
 * @param value
 * @return std::enable_if<std::is_floating_point<T>::value, T>::type
 */
template <typename T>
typename std::enable_if<std::is_floating_point<T>::value, T>::type asin(
    T value) {
  return std::asin(value);
}

/**
 * @brief arc cosine
 *
 * computes the arc cosine of the input value in radians
 *
 * @tparam T floating point type
 * @param value
 * @return std::enable_if<std::is_floating_point<T>::value, T>::type
 */
template <typename T>
typename std::enable_if<std::is_floating_point<T>::value, T>::type acos(
    T value) {
  return std::acos(value);
}

}  // namespace mu

#endif  // MU_UTILITY_H_