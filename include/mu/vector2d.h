#ifndef MU_VECTOR2D_H_
#define MU_VECTOR2D_H_

#include <vector.h>

namespace mu {

template <typename T>
class Vector2D : Vector<2, T> {
 public:
  Vector2D(T x, T y) {
    this->data_[0] = x;
    this->data_[1] = y;
  }
};

}  // namespace mu
#endif  // MU_VECTOR2D_H_