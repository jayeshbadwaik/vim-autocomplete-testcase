#ifndef VECTOR_HH
#define VECTOR_HH

#include <array>
#include <cassert>
#include <cmath>
#include <iostream>

namespace DGALE {
template <std::size_t nrow, std::size_t ncol>
class Matrix;

template <typename Base, std::size_t dim>
class VectorConversion {
};

template <typename Base>
class VectorConversion<Base, 1u> {
public:
  operator double() const
  {
    return static_cast<const Base&>(*this)[0];
  }
};

/// Euclidean vectors for two- and three-dimensional spaces.
template <std::size_t dimension>
class Vector : public VectorConversion<Vector<dimension>, dimension> {
public:
  /// Space Dimension of the Vector
  static const std::size_t dim = dimension;

  /// size_type for the underlying container.
  typedef typename std::array<double, dim>::size_type size_type;

  /// iterator for the underlying container
  typedef typename std::array<double, dim>::iterator iterator;

  /// const_iterator for the underlying container
  typedef typename std::array<double, dim>::const_iterator const_iterator;

private:
  /// co-ordinates of the point stored in the Vector
  std::array<double, dim> x;

public:
  // Default Constructor
  Vector() = default;

  /// Construct a vector with all components equal to s
  explicit Vector(const double s);

  /// Constructor from an array (List Initialization)
  explicit Vector(const std::array<double, dim> array);

  /// Return a vector with all components equal to s
  auto& operator=(const double s);

  /// Read Only Access to the i-th component of the vector (square brackets)
  auto operator[](const size_type i) const;

  /// Write Access to the i-th component of the vector (square brackets)
  auto& operator[](const size_type i);

  /// Add Vector v to the current vector and return the first Vector
  auto& operator+=(const Vector<dim>& v);

  /// Subtract Vector v from the first Vector and return the first vector
  auto& operator-=(const Vector<dim>& v);

  /// Multiple by a scalar s and return the vector
  auto& operator*=(const double s);

  /// Divide by a scalar s and return the vector
  auto& operator/=(const double s);

  // Norm
  auto norm(double order = 2) const;
};

// Dot Product
template <std::size_t dim>
auto dot(const Vector<dim>& a, const Vector<dim>& b);

// Outer Product
template <std::size_t ldim, std::size_t rdim>
auto outer(const Vector<ldim>& a, const Vector<rdim>& b);

// Cross Product for Certain Vectors
template <std::size_t dim>
auto cross(const Vector<dim>& a, const Vector<dim>& b);

/// Ofstream Operator for Printing
template <std::size_t dim>
std::ostream& operator<<(std::ostream& out, const Vector<dim>& v);

// Addition Operator
template <std::size_t dim>
auto operator+(const Vector<dim>& left, const Vector<dim>& right);

// Subtraction Operator
template <std::size_t dim>
auto operator-(const Vector<dim>& left, const Vector<dim>& right);

/// Multiply by a scalar s and return the result
template <std::size_t dim>
auto operator*(Vector<dim> v, const double s);
template <std::size_t dim>
auto operator*(const double s, Vector<dim> v);

/// Divide by a scalar s and return the result
template <std::size_t dim>
auto operator/(Vector<dim> v, const double s);

/// Divide by a scalar s and return the result
template <std::size_t dim>
auto operator/(Vector<dim> a, Vector<dim> b);
} // namespace DGALE

namespace std {

template <std::size_t dim>
auto pow(const DGALE::Vector<dim>& vector, double order);

template <std::size_t dim>
auto abs(const DGALE::Vector<dim>& vector);

template <std::size_t dim>
auto isnan(const DGALE::Vector<dim>& vector);

template <std::size_t dim>
auto cmax(const DGALE::Vector<dim>& a, const DGALE::Vector<dim>& b);
} // namespace std
#include "Vector.impl"
#endif // VECTOR_HH
