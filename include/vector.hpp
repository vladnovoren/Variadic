#include <cstddef>

template<typename ElemT, size_t Dim>
class Vector {
 public:
  template<typename... Args>
  Vector(Args... args) : components{args...} {
    static_assert(sizeof...(args) == Dim, "Wrong dimension");
  }

  ElemT& operator[](const size_t index) {
    return components[index];
  }

  const ElemT& operator[](const size_t index) const {
    return const_cast<Vector<ElemT, Dim>*>(this)->operator[](index);
  }

  ElemT operator*(const Vector& other) {
    return Dotter<Dim - 1>::DotProductImpl(*this, other);
  }

 private:
  static_assert(Dim != 0);

  template<size_t index>
  struct Dotter {
    static ElemT DotProductImpl(const Vector<ElemT, Dim>& a, const Vector<ElemT, Dim>& b) {
      return a[index] * b[index] + Dotter<index - 1>::DotProductImpl(a, b);
    }
  };

  ElemT components[Dim] = {};

};

template<typename ElemT, size_t Dim>
template<>
struct Vector<ElemT, Dim>::Dotter<0> {
  static ElemT DotProductImpl(const Vector<ElemT, Dim>& a, const Vector<ElemT, Dim>& b) {
    return a[0] * b[0];
  }
};
