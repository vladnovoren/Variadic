#include "vector.hpp"
#include <iostream>

int main() {
  Vector<int, 3> vec1(1, 2, 3);
  Vector<int, 3> vec2(1, 2, 3);
  std::cout << vec1 * vec2 << '\n';
  return 0;
}
