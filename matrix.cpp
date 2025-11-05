#include <cassert>
#include <iostream>
#include <vector>


template<typename Derived, typename T, size_t M, size_t N>
class BaseMatrix {
public:
  BaseMatrix() : data_(N, std::vector<T>(M, T())) {}
  explicit BaseMatrix(const std::vector<std::vector<T>>& vec) : data_(vec) {}
  explicit BaseMatrix(const T& elem) : data_(N, std::vector<T>(M, elem)) {}
  Derived& operator+=(const Derived& other) {
    for (size_t i = 0; i < N; ++i) {
      for (size_t j = 0; j < M; ++j) {
        data_[i][j] += other.data_[i][j];
      }
    }
    return static_cast<Derived&>(*this);
  }
  Derived& operator-=(const Derived& other) {
    for (size_t i = 0; i < N; ++i) {
      for (size_t j = 0; j < M; ++j) {
        data_[i][j] -= other.data_[i][j];
      }
    }
    return static_cast<Derived&>(*this);
  }
  Derived operator+(const Derived& other) const {
    Derived result = static_cast<const Derived&>(*this);
    result += other;
    return result;
  }
  Derived operator-(const Derived& other) const {
    Derived result = static_cast<const Derived&>(*this);
    result -= other;
    return result;
  }
  Derived operator*(const T& value) const {
    Derived result = static_cast<const Derived&>(*this);
    for (size_t i = 0; i < N; ++i) {
      for (size_t j = 0; j < M; ++j) {
        result.data_[i][j] *= value;
      }
    }
    return result;
  }
  T& operator()(size_t i, size_t j) {
    assert(i < N && j < M);
    return data_[i][j];
  }
  const T& operator()(size_t i, size_t j) const {
    assert(i < N && j < M);
    return data_[i][j];
  }
  Derived Transposed() const {
    Derived new_matrix;
    for (size_t i = 0; i < N; ++i) {
      for (size_t j = 0; j < M; ++j) {
        new_matrix.data_[i][j] = data_[j][i];
      }
    }
    return new_matrix;
  }
  bool operator==(const Derived& other) const {
    for (size_t i = 0; i < N; ++i) {
      for (size_t j = 0; j < M; ++j) {
        if (data_[i][j] != other.data_[i][j]) {
          return false;
        }
      }
    }
    return true;
  }
  bool operator!=(const Derived& other) const {
    return !(*this == other);
  }
  [[nodiscard]] const std::vector<std::vector<T>>& getData() const { return data_; }
  std::vector<std::vector<T>>& getData() { return data_; }

protected:
  std::vector<std::vector<T>> data_;

};
template<typename T, size_t M, size_t N>
class Matrix : public BaseMatrix<Matrix<T, M, N>, T, M, N> {
public:
  using BaseMatrix<Matrix<T, M, N>, T, M, N>::BaseMatrix;
  explicit Matrix(const BaseMatrix<Matrix<T, M, N>, T, M, N>& base)
          : BaseMatrix<Matrix<T, M, N>, T, M, N>(base.getData()) {}

};
template<typename T, size_t M>
class Matrix<T, M, M> : public BaseMatrix<Matrix<T, M, M>, T, M, M> {
public:
  using BaseMatrix<Matrix<T, M, M>, T, M, M>::BaseMatrix;
  explicit Matrix(const BaseMatrix<Matrix<T, M, M>, T, M, M>& base)
          : BaseMatrix<Matrix<T, M, M>, T, M, M>(base.getData()) {}
  void Trace() const{
    for (size_t i = 0; i < M; ++i) {
      std::cout << BaseMatrix<Matrix<T, M, M>, T, M, M>::data_[i][i] << " ";
    }
    std::cout << "\n";
  }
};

int main() {
  Matrix<int, 5, 4> m(5);
  auto m3 = m;
  m3(1, 1) = 3;
  std::cout << (m == m3);
}



