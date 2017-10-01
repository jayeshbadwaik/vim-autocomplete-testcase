#include "Vector.hh"
#include "matrix.hh"
#include <cassert>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <type_traits>

int main()
{

  const double tolerance = std::numeric_limits<double>::epsilon();

  assert(static_cast<bool>(std::is_pod<DGALE::Vector<1>>::value));
  assert(static_cast<bool>(std::is_pod<DGALE::Vector<2>>::value));
  assert(static_cast<bool>(std::is_pod<DGALE::Matrix<1, 1>>::value));
  assert(static_cast<bool>(std::is_pod<DGALE::Matrix<2, 1>>::value));
  assert(static_cast<bool>(std::is_pod<DGALE::Matrix<1, 2>>::value));

  using Vec1D = DGALE::Vector<1>;
  using Vec2D = DGALE::Vector<2>;
  using Mat1x1D = DGALE::Matrix<1, 1>;
  using Mat1x2D = DGALE::Matrix<1, 2>;
  using Mat2x1D = DGALE::Matrix<2, 1>;
  using Mat2x2D = DGALE::Matrix<2, 2>;
  Vec2D vec0 __attribute__((unused));
  Mat2x2D mat0 __attribute__((unused));

  Vec2D vec1(3);
  assert(std::abs(vec1[0] - 3) < tolerance);
  assert(std::abs(vec1[1] - 3) < tolerance);

  Mat2x2D mat1(3);
  assert(std::abs(mat1[0][0] - 3) < tolerance);
  assert(std::abs(mat1[0][1] - 3) < tolerance);
  assert(std::abs(mat1[1][0] - 3) < tolerance);
  assert(std::abs(mat1[1][1] - 3) < tolerance);

  Vec2D vec2{{{1, 2}}};
  assert(std::abs(vec2[0] - 1) < tolerance);
  assert(std::abs(vec2[1] - 2) < tolerance);

  Mat2x2D mat2{{{{{1, 2}}, {{3, 5}}}}};
  assert(std::abs(mat2[0][0] - 1) < tolerance);
  assert(std::abs(mat2[0][1] - 2) < tolerance);
  assert(std::abs(mat2[1][0] - 3) < tolerance);
  assert(std::abs(mat2[1][1] - 5) < tolerance);

  Vec2D vec3;
  vec3 = 3.0;
  assert(std::abs(vec3[0] - 3) < tolerance);
  assert(std::abs(vec3[1] - 3) < tolerance);

  Mat2x2D mat3;
  mat3 = 3.0;
  assert(std::abs(mat3[0][0] - 3) < tolerance);
  assert(std::abs(mat3[0][1] - 3) < tolerance);
  assert(std::abs(mat3[1][0] - 3) < tolerance);
  assert(std::abs(mat3[1][1] - 3) < tolerance);

  Vec2D vec4{1};
  Mat1x2D mat5{3};
  Mat2x1D mat6{7};
  vec4 = mat5;
  assert(std::abs(vec4[0] - 3) < tolerance);
  assert(std::abs(vec4[1] - 3) < tolerance);
  vec4 = mat6;
  assert(std::abs(vec4[0] - 7) < tolerance);
  assert(std::abs(vec4[1] - 7) < tolerance);

  Vec1D vec6{0};
  double scalar0 = 5;
  scalar0 = vec6;
  assert(std::abs(scalar0 - 0) < tolerance);

  Mat1x1D mat7{0};
  double scalar1 = 5;
  scalar1 = mat7;
  assert(std::abs(scalar1 - 0) < tolerance);

  Vec2D vec7{0};
  vec7[1] = 2;
  assert(std::abs(vec7[0] - 0) < tolerance);
  assert(std::abs(vec7[1] - 2) < tolerance);

  Vec2D vec8{4};
  Vec2D vec9{5};
  vec8 += vec9;
  assert(std::abs(vec8[0] - 9) < tolerance);
  assert(std::abs(vec8[1] - 9) < tolerance);
  vec8 -= vec9;
  assert(std::abs(vec8[0] - 4) < tolerance);
  assert(std::abs(vec8[1] - 4) < tolerance);
  vec8 *= 2;
  assert(std::abs(vec8[0] - 8) < tolerance);
  assert(std::abs(vec8[1] - 8) < tolerance);
  vec8 /= 2;
  assert(std::abs(vec8[0] - 4) < tolerance);
  assert(std::abs(vec8[1] - 4) < tolerance);

  vec9 = vec8 * 2;
  assert(std::abs(vec9[0] - 8) < tolerance);
  assert(std::abs(vec9[1] - 8) < tolerance);

  vec9 = vec8 / 2;
  assert(std::abs(vec9[0] - 2) < tolerance);
  assert(std::abs(vec9[1] - 2) < tolerance);

  vec9 = 2 * vec8;
  assert(std::abs(vec9[0] - 8) < tolerance);
  assert(std::abs(vec9[1] - 8) < tolerance);

  Vec2D vec10 = vec9 + vec8;
  assert(std::abs(vec10[0] - 12) < tolerance);
  assert(std::abs(vec10[1] - 12) < tolerance);

  vec10 = vec9 - vec8;
  assert(std::abs(vec10[0] - 4) < tolerance);
  assert(std::abs(vec10[1] - 4) < tolerance);

  vec10 = std::pow(vec9, 2);
  assert(std::abs(vec10[0] - 64) < tolerance);
  assert(std::abs(vec10[1] - 64) < tolerance);

  auto scalar3 = dot(vec9, vec8);
  assert(std::abs(scalar3 - 64) < tolerance);

  auto m = outer(vec8, vec9);
  vec9 = -8;
  assert(std::abs(vec9.norm(1) - 16) < tolerance);
  assert(std::abs(vec9.norm(1) - 16) < tolerance);

  vec10 = std::abs(vec9);
  assert(std::abs(vec10[0] - 8) < tolerance);
  assert(std::abs(vec10[1] - 8) < tolerance);

  auto mat8 = outer(vec8, vec9);
  std::cout << mat8 << std::endl;

  vec10 = cross(vec8, vec9);
  std::cout << vec10 << std::endl;

  Vec2D vec11{{{3, 4}}};
  assert(std::abs(vec11.norm() - 5) < tolerance);

  return 0;
}
