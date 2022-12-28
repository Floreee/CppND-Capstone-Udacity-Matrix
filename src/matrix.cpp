#include <string>
#include <vector>
#include <thread>
#include <mutex>
#include <chrono>
#include <iostream>
#include <random>
#include <algorithm>
#include "matrix.h"

using namespace Udacity;

template <typename T> Matrix<T>::Matrix() : _rows(0), _cols(0)
{
}

template <typename T> Matrix<T>::Matrix(int rows, int cols) : _rows(rows), _cols(cols)
{
  _data.resize(rows);
  for (int i = 0; i < rows; i++)
  {
    _data[i].resize(cols);
  }
}

template <typename T> Matrix<T>::Matrix(const Matrix &other) : _rows(other._rows), _cols(other._cols), _data(other._data)
{
}

template <typename T> Matrix<T>::Matrix(Matrix &&other) : _rows(other._rows), _cols(other._cols), _data(std::move(other._data))
{
  other._rows = 0;
  other._cols = 0;
}

template <typename T> Matrix<T>::~Matrix()
{
}

template <typename T> void Matrix<T>::set(int r, int c, T value)
{
  _data[r][c] = value;
}

template <typename T> std::vector<std::vector<T>> Matrix<T>::get()
{
  return _data;
}

template <typename T> T Matrix<T>::get(int r, int c) const
{
  return _data[r][c];
}

template <typename T> int Matrix<T>::getRows() const
{
  return _rows;
}

template <typename T> int Matrix<T>::getCols() const
{
  return _cols;
}

template <typename T> Matrix<T> &Matrix<T>::operator=(const Matrix &other)
{
  _rows = other._rows;
  _cols = other._cols;
  _data = other._data;
  return *this;
}

template <typename T> Matrix<T> &Matrix<T>::operator=(Matrix &&other)
{
  _rows = other._rows;
  _cols = other._cols;
  _data = std::move(other._data);
  other._rows = 0;
  other._cols = 0;
  return *this;
}

template <typename T> Matrix<T> Matrix<T>::operator*(const Matrix &other)
{
  if (_cols != other.getRows())
  {
    throw std::invalid_argument("Incompatible matrix dimensions for multiplication.");
  }
    return multiply(other);
}

template <typename T> Matrix<T> Matrix<T>::operator*(T scalar) const
{
  Matrix result(_rows, _cols);
  for (int i = 0; i < _rows; i++)
  {
    for (int j = 0; j < _cols; j++)
    {
      result.set(i, j, _data[i][j] * scalar);
    }
  }
  return result;
}

template <typename T> Matrix<T> Matrix<T>::operator/(T scalar) {
  Matrix result(_rows, _cols);
  for (int i = 0; i < _rows; i++) {
    for (int j = 0; j < _cols; j++) {
      result.set(i, j, (T) _data[i][j] / scalar);
    }
  }
  return result;
}

template <typename T> bool Matrix<T>::operator==(const Matrix &other) const
{
  if (_rows != other.getRows() || _cols != other.getCols())
  {
    return false;
  }
  for (int i = 0; i < _rows; i++)
  {
    for (int j = 0; j < _cols; j++)
    {
      if (_data[i][j] != other.get(i, j))
      {
        return false;
      }
    }
  }
  return true;
}

template <typename T> Matrix<T> Matrix<T>::operator+(const Matrix &other) const
{
  if (_rows != other.getRows() || _cols != other.getCols())
  {
    throw std::invalid_argument("Incompatible matrix dimensions for addition.");
  }
  Matrix result(_rows, _cols);
  for (int i = 0; i < _rows; i++)
  {
    for (int j = 0; j < _cols; j++)
    {
      result.set(i, j, _data[i][j] + other.get(i, j));
    }
  }
  return result;
}

template <typename T> Matrix<T> Matrix<T>::operator-(const Matrix &other) const
{
  if (_rows != other.getRows() || _cols != other.getCols())
  {
    throw std::invalid_argument("Incompatible matrix dimensions for addition.");
  }
  Matrix result(_rows, _cols);
  for (int i = 0; i < _rows; i++)
  {
    for (int j = 0; j < _cols; j++)
    {
      result.set(i, j, _data[i][j] - other.get(i, j));
    }
  }
  return result;
}

template <typename T> T &Matrix<T>::operator()(int r, int c)
{
  return _data[r][c];
}

template <typename T> void Matrix<T>::random()
{
  std::mt19937 mt{static_cast<unsigned int>(
      std::chrono::steady_clock::now().time_since_epoch().count())};
  std::uniform_int_distribution dis{0, 255};

  for (int i = 0; i < this->getRows(); i++)
  {
    for (int j = 0; j < this->getCols(); j++)
    {
      _data[i][j] = dis(mt);
    } 
  }
}

template <typename T> Matrix<T> Matrix<T>::multiply(const Matrix &other)
{
  if (_cols != other.getRows())
  {
    throw std::invalid_argument("Incompatible matrix dimensions for multiplication.");
  }
  Matrix result(_rows, other.getCols());
  for (int i = 0; i < _rows; i++)
  {
    for (int j = 0; j < other.getCols(); j++)
    {
      int sum = 0;
      for (int k = 0; k < _cols; k++)
      {
        sum += get(i, k) * other.get(k, j);
      }
      result.set(i, j, sum);
    }
  }

  return result;
}

template <typename T> Matrix<T> Matrix<T>::multiplyParallel(const Matrix &other, int numThreads)
{
  if (this->getCols() != other.getRows())
  {
    throw std::invalid_argument("Incompatible matrix dimensions for multiplication.");
  }
  Matrix result(this->getRows(), other.getCols());

  // Create a vector of threads
  std::vector<std::thread> threads;
  for (int t = 0; t < numThreads; t++)
  {
    threads.emplace_back(&Matrix::multiplyParallel_Thread, this, std::ref(other), std::ref(result), t, numThreads);
  }

  // Wait for all threads to finish
  for (auto &thread : threads)
  {
    thread.join();
  }

  return result;
}

template <typename T> void Matrix<T>::multiplyParallel_Thread(const Matrix &other, Matrix &result, int threadId, int numThreads)
{
  // Calculate the rows that this thread is responsible for
  int rowsPerThread = this->getRows() / numThreads;
  int startRow = threadId * rowsPerThread;
  int endRow = startRow + rowsPerThread;

  // Perform the matrix multiplication
  for (int i = startRow; i < endRow; i++)
  {
    for (int j = 0; j < other.getCols(); j++)
    {
      int sum = 0;
      for (int k = 0; k < this->getCols(); k++)
      {
        sum += get(i, k) * other.get(k, j);
      }
      // Use a mutex to protect the shared result matrix
      std::lock_guard<std::mutex> lock(_mtx);
      result.set(i, j, sum);
    }
  }
}

template <typename T> Matrix<T> Matrix<T>::inverse() {
  if (_rows != _cols) {
    throw std::invalid_argument("Matrix is not square!");
  }

  double det = determinant();
  if (std::abs(det) < 1e-9) {
    throw std::invalid_argument("Matrix is singular!");
  }

  Matrix adjoint = this->adjoint();
  return adjoint / det;
}

template <typename T> T Matrix<T>::determinant() {
  if (_rows != _cols) {
    throw std::invalid_argument("Matrix is not square!");
  }

  if (_rows == 1) {
    return _data[0][0];
  } else if (_rows == 2) {
    return _data[0][0] * _data[1][1] - _data[0][1] * _data[1][0];
  } else {
    double det = 0;
    for (int i = 0; i < _cols; i++) {
      det += std::pow(-1, i) * _data[0][i] * minor(0, i).determinant();
    }
    return det;
  }
}

template <typename T> Matrix<T> Matrix<T>::minor(int r, int c) {
  Matrix result(_rows - 1, _cols - 1);
  int k = 0;
  int l = 0;
  for (int i = 0; i < _rows; i++) {
    if (i == r) {
      continue;
    }
    l = 0;
    for (int j = 0; j < _cols; j++) {
      if (j == c) {
        continue;
      }
      result(k, l) = _data[i][j];
      l++;
    }
    k++;
  }
  return result;
}

template <typename T> Matrix<T> Matrix<T>::adjoint() {
  Matrix result(_rows, _cols);
  for (int i = 0; i < _rows; i++) {
    for (int j = 0; j < _cols; j++) {
      result(i, j) = std::pow(-1, i + j) * minor(i, j).determinant();
    }
  }
  return result.transpose();
}

template <typename T> Matrix<T> Matrix<T>::transpose() const
{
  Matrix result(_cols, _rows);
  for (int i = 0; i < _rows; i++)
  {
    for (int j = 0; j < _cols; j++)
    {
      result.set(j, i, _data[i][j]);
    }
  }
  return result;
}

template <typename T> void Matrix<T>::resize(int new_rows, int new_cols) 
{
  _data.resize(new_rows);
  for (int i = 0; i < new_rows; i++)
  {
    _data[i].resize(new_cols);
  }

  _rows = new_rows;
  _cols = new_cols;
}

template <typename T> void Matrix<T>::print()
{
  for (int i = 0; i < _rows; i++)
  {
    for (int j = 0; j < _cols; j++)
    {
      std::cout << (*this)(i, j) << " ";
    }
    std::cout << std::endl;
  }
}

// Allow possible template classes
template class Matrix<int>;
template class Matrix<float>;
template class Matrix<double>;