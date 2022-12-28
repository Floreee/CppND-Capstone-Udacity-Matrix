#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <string>
#include <mutex>

namespace Udacity
{
    template <typename T>
    class Matrix
    {
    public:
        // C'tors
        Matrix();
        Matrix(const Matrix &other);
        Matrix(Matrix &&other);
        Matrix(int rows, int cols);
        virtual ~Matrix();

        // Getter/Setter
        std::vector<std::vector<T>> get();
        T get(int row, int col) const;
        void set(int row, int col, T value);
        int getRows() const;
        int getCols() const;

        // Fill matrix with random values
        void random();

        // Overload operators
        Matrix operator*(const Matrix &other);
        Matrix operator*(T scalar) const;
        Matrix operator/(T scalar);
        Matrix operator+(const Matrix &other) const;
        Matrix operator-(const Matrix &other) const;
        Matrix &operator=(const Matrix &other);
        Matrix &operator=(Matrix &&other);
        bool operator==(const Matrix &other) const;
        T &operator()(int i, int j);

        // Matrix operations
        Matrix multiply(const Matrix &other);
        Matrix multiplyParallel(const Matrix &other, int numThreads);
        Matrix inverse();
        Matrix transpose() const;
        T determinant();
        Matrix minor(int r, int c);
        Matrix adjoint();
        void resize(int new_rows, int new_cols);
        void print();

    private:
        std::vector<std::vector<T>> _data;
        int _rows, _cols;
        std::mutex _mtx;
        void multiplyParallel_Thread(const Matrix &other, Matrix &result, int threadId, int numThreads);
    };
}
#endif