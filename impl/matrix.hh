#ifndef MATRIX_HH
#define MATRIX_HH

#include "Vector.hh"
#include <array>
#include <type_traits>

namespace DGALE {
template <typename Base, std::size_t nrow, std::size_t ncol>
class MatrixConversion {
};

template <typename Base, std::size_t ncol>
class MatrixConversion<Base, 1u, ncol> {
public:
  operator Vector<ncol>() const
  {
    return static_cast<const Base&>(*this)[0];
  }
};

template <typename Base, std::size_t nrow>
class MatrixConversion<Base, nrow, 1u> {
public:
  operator Vector<nrow>() const
  {
    Vector<nrow> result;
    for (std::size_t i = 0; i < nrow; ++i) {
      result[i] = static_cast<const Base&>(*this)[i][0];
    }
    return result;
  }
};

template <typename Base>
class MatrixConversion<Base, 1u, 1u> {
public:
  operator double() const
  {
    return static_cast<const Base&>(*this)[0][0];
  }
};

template <std::size_t numrow, std::size_t numcol = numrow>
class Matrix : public MatrixConversion<Matrix<numrow, numcol>, numrow, numcol> {
public:
  // Dimension Variables
  static const std::size_t nrow = numrow;
  static const std::size_t ncol = numcol;

  using VType = Vector<ncol>;
  /// size_type for the underlying container.
  typedef typename std::array<VType, nrow>::size_type size_type;

  /// iterator for the underlying container
  typedef typename std::array<VType, nrow>::iterator iterator;

  /// const_iterator for the underlying container
  typedef typename std::array<VType, nrow>::const_iterator const_iterator;

private:
  /// Elements of the Matrix (row wise storage)
  /// (i,j) element is given by i*ncol + j
  std::array<VType, nrow> x;

public:
  /// Default Constructor
  Matrix() = default;

  /// Construct a matrix with all components equal to s
  explicit Matrix(const double s);

  /// Constructor from an double array (List Initialization)
  explicit Matrix(const std::array<std::array<double, ncol>, nrow> nestedarray);

  // Assignment operator for scalar
  auto& operator=(const double s);
  template <std::size_t cols,
            typename std::enable_if<cols == ncol && ncol != 1
                                    && nrow == 1>::type* = nullptr>
  auto& operator=(Vector<cols> v)
  {
    x.fill(v);
    return *this;
  }

  template <std::size_t rows,
            typename std::enable_if<rows == nrow && nrow != 1
                                    && ncol == 1>::type* = nullptr>
  auto& operator=(Vector<rows> v)
  {
    for (std::size_t row = 0; row < nrow; ++row) {
      x[row][0] = v[row];
    }
    return *this;
  }

  /// Read Only Access to the i-th component of the vector (square brackets)
  auto operator[](const size_type i) const;

  /// Write Access to the i-th component of the vector (square brackets)
  auto& operator[](const size_type i);

  // Read Only Access to the i-th column of the matrix
  auto col(const size_type i) const;

  // Matrix Addition Operator
  auto& operator+=(const Matrix<nrow, ncol>& m);

  // Matrix Subtraction Operator
  auto& operator-=(const Matrix<nrow, ncol>& m);

  /// Multiple by a scalar s and return the matrix
  auto& operator*=(const double s);

  /// Divide by a scalar s and return the matrix
  auto& operator/=(const double s);

  // Norm
  auto norm(double order = 2) const;
};

// Dot Product
template <std::size_t nrow, std::size_t ncol>
auto dot(const Vector<nrow>& a, const Matrix<nrow, ncol>& b);

template <std::size_t nrow, std::size_t ncol>
auto dot(const Matrix<nrow, ncol>& a, const Vector<ncol>& b);

// Dot Product with a Matrix
template <std::size_t nrow, std::size_t ncol, std::size_t rncol>
auto dot(Matrix<nrow, ncol> a, Matrix<ncol, rncol> b);

// Ofstream Operator for Printing
template <std::size_t nrow, std::size_t ncol>
std::ostream& operator<<(std::ostream& out, const Matrix<nrow, ncol>& m);

template <std::size_t nrow, std::size_t ncol>
auto operator+(Matrix<nrow, ncol> left, const Matrix<nrow, ncol>& right);

template <std::size_t nrow, std::size_t ncol>
auto operator-(Matrix<nrow, ncol> left, const Matrix<nrow, ncol>& right);

template <std::size_t nrow, std::size_t ncol>
auto operator*(Matrix<nrow, ncol> left, double scalar);

template <std::size_t nrow, std::size_t ncol>
auto operator*(double scalar, Matrix<nrow, ncol> right);

template <std::size_t nrow, std::size_t ncol>
auto operator/(Matrix<nrow, ncol> left, double scalar);
} // namespace DGALE

namespace std {

template <std::size_t nrow, std::size_t ncol>
auto pow(const DGALE::Matrix<nrow, ncol>& m, double order);

template <std::size_t nrow, std::size_t ncol>
auto abs(const DGALE::Matrix<nrow, ncol>& m);

template <std::size_t nrow, std::size_t ncol>
auto isnan(const DGALE::Matrix<nrow, ncol>& m);
} // namespace std
#include "matrix.impl"
#endif // MATRIX_HH
