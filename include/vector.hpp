#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <cstddef>

template <typename ElemT, size_t Dim>
class Vector;

template <size_t index, typename ElemT, size_t Dim>
struct Dotter {
  static ElemT DotProductImpl(const Vector<ElemT, Dim> &lhs,
                              const Vector<ElemT, Dim> &rhs) {
    return lhs[index] * lhs[index] +
           Dotter<index - 1, ElemT, Dim>::DotProductImpl(lhs, rhs);
  }
};

template <typename ElemT, size_t Dim>
struct Dotter<0, ElemT, Dim> {
  static ElemT DotProductImpl(const Vector<ElemT, Dim> &lhs,
                              const Vector<ElemT, Dim> &rhs) {
    return lhs[0] * lhs[0];
  }
};

template <typename ElemT, size_t Dim> class Vector {
public:
  template <typename... Args> Vector(Args... args) : components{args...} {
    static_assert(sizeof...(args) == Dim, "Wrong dimension");
  }

  ElemT &operator[](const size_t index) { return components[index]; }

  const ElemT &operator[](const size_t index) const {
    return const_cast<Vector<ElemT, Dim> *>(this)->operator[](index);
  }

  ElemT operator*(const Vector &other) {
    return Dotter<Dim - 1, ElemT, Dim>::DotProductImpl(*this, other);
  }

private:
  static_assert(Dim != 0);

  ElemT components[Dim] = {};
};

#endif /* vector.hpp */
