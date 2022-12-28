#include "matrix.h"
#include "test.h"
#include <cassert>
#include <iostream>

// using namespace Udacity;

void test()
{
    // Testing default constructor
    Udacity::Matrix<int> matrix1;
    assert(matrix1.getRows() == 0);
    assert(matrix1.getCols() == 0);

    // Testing copy constructor
    Udacity::Matrix<int> matrix2(2, 3);
    matrix2.set(0, 0, 1);
    matrix2.set(0, 1, 2);
    matrix2.set(0, 2, 3);
    matrix2.set(1, 0, 4);
    matrix2.set(1, 1, 5);
    matrix2.set(1, 2, 6);

    Udacity::Matrix<int> matrix3(matrix2);
    assert(matrix3.getRows() == 2);
    assert(matrix3.getCols() == 3);
    assert(matrix3.get(0, 0) == 1);
    assert(matrix3.get(0, 1) == 2);
    assert(matrix3.get(0, 2) == 3);
    assert(matrix3.get(1, 0) == 4);
    assert(matrix3.get(1, 1) == 5);
    assert(matrix3.get(1, 2) == 6);

    // Testing move constructor
    Udacity::Matrix<int> matrix4(2, 3);
    matrix4.set(0, 0, 1);
    matrix4.set(0, 1, 2);
    matrix4.set(0, 2, 3);
    matrix4.set(1, 0, 4);
    matrix4.set(1, 1, 5);
    matrix4.set(1, 2, 6);

    Udacity::Matrix<int> matrix5(std::move(matrix4));
    assert(matrix5.getRows() == 2);
    assert(matrix5.getCols() == 3);
    assert(matrix5.get(0, 0) == 1);
    assert(matrix5.get(0, 1) == 2);
    assert(matrix5.get(0, 2) == 3);
    assert(matrix5.get(1, 0) == 4);
    assert(matrix5.get(1, 1) == 5);
    assert(matrix5.get(1, 2) == 6);

    // Testing parameterized constructor
    Udacity::Matrix<int> matrix6(2, 3);
    assert(matrix6.getRows() == 2);
    assert(matrix6.getCols() == 3);

    // Testing getter/setter functions
    Udacity::Matrix<int> matrix7(2, 3);
    matrix7.set(0, 0, 1);
    matrix7.set(0, 1, 2);
    matrix7.set(0, 2, 3);
    matrix7.set(1, 0, 4);
    matrix7.set(1, 1, 5);
    matrix7.set(1, 2, 6);

    assert(matrix7.getRows() == 2);
    assert(matrix7.getCols() == 3);
    assert(matrix7.get(0, 0) == 1);
    assert(matrix7.get(0, 1) == 2);
    assert(matrix7.get(0, 2) == 3);
    assert(matrix7.get(1, 0) == 4);
    assert(matrix7.get(1, 1) == 5);
    assert(matrix7.get(1, 2) == 6);

    std::vector<std::vector<int>> data = matrix7.get();
    assert(data[0][0] == 1);
    assert(data[0][1] == 2);
    assert(data[0][2] == 3);
    assert(data[1][0] == 4);
    assert(data[1][1] == 5);
    assert(data[1][2] == 6);

    // Testing get function
    Udacity::Matrix<int> matrix8(2, 3);
    matrix8.set(0, 0, 1);
    matrix8.set(0, 1, 2);
    matrix8.set(0, 2, 3);
    matrix8.set(1, 0, 4);
    matrix8.set(1, 1, 5);
    matrix8.set(1, 2, 6);

    assert(matrix8.get(0, 0) == 1);
    assert(matrix8.get(0, 1) == 2);
    assert(matrix8.get(0, 2) == 3);
    assert(matrix8.get(1, 0) == 4);
    assert(matrix8.get(1, 1) == 5);
    assert(matrix8.get(1, 2) == 6);

    // Testing `set` function
    Udacity::Matrix<int> matrix9(2, 3);
    matrix9.set(0, 0, 10);
    matrix9.set(0, 1, 20);
    matrix9.set(0, 2, 30);
    matrix9.set(1, 0, 40);
    matrix9.set(1, 1, 50);
    matrix9.set(1, 2, 60);

    assert(matrix9.get(0, 0) == 10);
    assert(matrix9.get(0, 1) == 20);
    assert(matrix9.get(0, 2) == 30);
    assert(matrix9.get(1, 0) == 40);
    assert(matrix9.get(1, 1) == 50);
    assert(matrix9.get(1, 2) == 60);

    // Testing `getRows` and `getCols`
    Udacity::Matrix<int> matrix10(4, 5);
    assert(matrix10.getRows() == 4);
    assert(matrix10.getCols() == 5);

    // Testing `random` function
    Udacity::Matrix<int> matrix48(2, 3);
    matrix48.random();

    // Testing `operator*` function with two matrices
    Udacity::Matrix<int> matrix49(2, 3);
    matrix49.set(0, 0, 1);
    matrix49.set(0, 1, 2);
    matrix49.set(0, 2, 3);
    matrix49.set(1, 0, 4);
    matrix49.set(1, 1, 5);
    matrix49.set(1, 2, 6);

    Udacity::Matrix<int> matrix50(3, 2);
    matrix50.set(0, 0, 7);
    matrix50.set(0, 1, 8);
    matrix50.set(1, 0, 9);
    matrix50.set(1, 1, 10);
    matrix50.set(2, 0, 11);
    matrix50.set(2, 1, 12);

    Udacity::Matrix<int> matrix51 = matrix49 * matrix50;
    assert(matrix51.getRows() == 2);
    assert(matrix51.getCols() == 2);
    assert(matrix51.get(0, 0) == 58);
    assert(matrix51.get(0, 1) == 64);
    assert(matrix51.get(1, 0) == 139);
    assert(matrix51.get(1, 1) == 154);

    // Testing `operator*` function with a matrix and a scalar
    Udacity::Matrix<int> matrix52(2, 3);
    matrix52.set(0, 0, 1);
    matrix52.set(0, 1, 2);
    matrix52.set(0, 2, 3);
    matrix52.set(1, 0, 4);
    matrix52.set(1, 1, 5);
    matrix52.set(1, 2, 6);

    Udacity::Matrix<int> matrix53 = matrix52 * 3;
    assert(matrix53.getRows() == 2);
    assert(matrix53.getCols() == 3);
    assert(matrix53.get(0, 0) == 3);
    assert(matrix53.get(0, 1) == 6);
    assert(matrix53.get(0, 2) == 9);
    assert(matrix53.get(1, 0) == 12);
    assert(matrix53.get(1, 1) == 15);
    assert(matrix53.get(1, 2) == 18);

    // Testing `operator/` function
    Udacity::Matrix<int> matrix54(2, 3);
    matrix54.set(0, 0, 6);
    matrix54.set(0, 1, 12);
    matrix54.set(0, 2, 18);
    matrix54.set(1, 0, 24);
    matrix54.set(1, 1, 30);
    matrix54.set(1, 2, 36);

    Udacity::Matrix<int> matrix55 = matrix54 / 2;
    assert(matrix55.getRows() == 2);
    assert(matrix55.getCols() == 3);
    assert(matrix55.get(0, 0) == 3);
    assert(matrix55.get(0, 1) == 6);
    assert(matrix55.get(0, 2) == 9);
    assert(matrix55.get(1, 0) == 12);
    assert(matrix55.get(1, 1) == 15);
    assert(matrix55.get(1, 2) == 18);

    // Testing `operator+` function
    Udacity::Matrix<int> matrix56(2, 3);
    matrix56.set(0, 0, 1);
    matrix56.set(0, 1, 2);
    matrix56.set(0, 2, 3);
    matrix56.set(1, 0, 4);
    matrix56.set(1, 1, 5);
    matrix56.set(1, 2, 6);

    Udacity::Matrix<int> matrix57(2, 3);
    matrix57.set(0, 0, 6);
    matrix57.set(0, 1, 5);
    matrix57.set(0, 2, 4);
    matrix57.set(1, 0, 3);
    matrix57.set(1, 1, 2);
    matrix57.set(1, 2, 1);

    Udacity::Matrix<int> matrix58 = matrix56 + matrix57;
    assert(matrix58.getRows() == 2);
    assert(matrix58.getCols() == 3);
    assert(matrix58.get(0, 0) == 7);
    assert(matrix58.get(0, 1) == 7);
    assert(matrix58.get(0, 2) == 7);
    assert(matrix58.get(1, 0) == 7);
    assert(matrix58.get(1, 1) == 7);
    assert(matrix58.get(1, 2) == 7);

    // Testing `operator-` function
    Udacity::Matrix<int> matrix59(2, 3);
    matrix59.set(0, 0, 1);
    matrix59.set(0, 1, 2);
    matrix59.set(0, 2, 3);
    matrix59.set(1, 0, 4);
    matrix59.set(1, 1, 5);
    matrix59.set(1, 2, 6);

    Udacity::Matrix<int> matrix60(2, 3);
    matrix60.set(0, 0, 6);
    matrix60.set(0, 1, 5);
    matrix60.set(0, 2, 4);
    matrix60.set(1, 0, 3);
    matrix60.set(1, 1, 2);
    matrix60.set(1, 2, 1);

    Udacity::Matrix<int> matrix61 = matrix59 - matrix60;
    assert(matrix61.getRows() == 2);
    assert(matrix61.getCols() == 3);
    assert(matrix61.get(0, 0) == -5);
    assert(matrix61.get(0, 1) == -3);
    assert(matrix61.get(0, 2) == -1);
    assert(matrix61.get(1, 0) == 1);
    assert(matrix61.get(1, 1) == 3);
    assert(matrix61.get(1, 2) == 5);

    // Testing `operator=` function with copy assignment
    Udacity::Matrix<int> matrix62(2, 3);
    matrix62.set(0, 0, 1);
    matrix62.set(0, 1, 2);
    matrix62.set(0, 2, 3);
    matrix62.set(1, 0, 4);
    matrix62.set(1, 1, 5);
    matrix62.set(1, 2, 6);

    Udacity::Matrix<int> matrix63;
    matrix63 = matrix62;
    assert(matrix63.getRows() == 2);
    assert(matrix63.getCols() == 3);
    assert(matrix63.get(0, 0) == 1);
    assert(matrix63.get(0, 1) == 2);
    assert(matrix63.get(0, 2) == 3);
    assert(matrix63.get(1, 0) == 4);
    assert(matrix63.get(1, 1) == 5);
    assert(matrix63.get(1, 2) == 6);

    // Testing `operator=` function with move assignment
    Udacity::Matrix<int> matrix64(2, 3);
    matrix64.set(0, 0, 1);
    matrix64.set(0, 1, 2);
    matrix64.set(0, 2, 3);
    matrix64.set(1, 0, 4);
    matrix64.set(1, 1, 5);
    matrix64.set(1, 2, 6);

    Udacity::Matrix<int> matrix65;
    matrix65 = std::move(matrix64);
    assert(matrix65.getRows() == 2);
    assert(matrix65.getCols() == 3);
    assert(matrix65.get(0, 0) == 1);
    assert(matrix65.get(0, 1) == 2);
    assert(matrix65.get(0, 2) == 3);
    assert(matrix65.get(1, 0) == 4);
    assert(matrix65.get(1, 1) == 5);
    assert(matrix65.get(1, 2) == 6);

    // Testing `operator==` function
    Udacity::Matrix<int> matrix66(2, 3);
    matrix66.set(0, 0, 1);
    matrix66.set(0, 1, 2);
    matrix66.set(0, 2, 3);
    matrix66.set(1, 0, 4);
    matrix66.set(1, 1, 5);
    matrix66.set(1, 2, 6);

    Udacity::Matrix<int> matrix67(2, 3);
    matrix67.set(0, 0, 1);
    matrix67.set(0, 1, 2);
    matrix67.set(0, 2, 3);
    matrix67.set(1, 0, 4);
    matrix67.set(1, 1, 5);
    matrix67.set(1, 2, 6);

    assert(matrix66 == matrix67);

    Udacity::Matrix<int> matrix68(2, 3);
    matrix68.set(0, 0, 6);
    matrix68.set(0, 1, 5);
    matrix68.set(0, 2, 4);
    matrix68.set(1, 0, 3);
    matrix68.set(1, 1, 2);
    matrix68.set(1, 2, 1);

    assert(!(matrix66 == matrix68));

    // Testing `operator()` function
    Udacity::Matrix<int> matrix69(2, 3);
    matrix69.set(0, 0, 1);
    matrix69.set(0, 1, 2);
    matrix69.set(0, 2, 3);
    matrix69.set(1, 0, 4);
    matrix69.set(1, 1, 5);
    matrix69.set(1, 2, 6);

    assert(matrix69(0, 0) == 1);
    assert(matrix69(0, 1) == 2);
    assert(matrix69(0, 2) == 3);
    assert(matrix69(1, 0) == 4);
    assert(matrix69(1, 1) == 5);
    assert(matrix69(1, 2) == 6);

    matrix69(0, 0) = 10;
    matrix69(0, 1) = 20;
    matrix69(0, 2) = 30;
    matrix69(1, 0) = 40;
    matrix69(1, 1) = 50;
    matrix69(1, 2) = 60;

    assert(matrix69(0, 0) == 10);
    assert(matrix69(0, 1) == 20);
    assert(matrix69(0, 2) == 30);
    assert(matrix69(1, 0) == 40);
    assert(matrix69(1, 1) == 50);
    assert(matrix69(1, 2) == 60);

    // Testing `multiply` function
    Udacity::Matrix<int> matrix70(2, 3);
    matrix70.set(0, 0, 1);
    matrix70.set(0, 1, 2);
    matrix70.set(0, 2, 3);
    matrix70.set(1, 0, 4);
    matrix70.set(1, 1, 5);
    matrix70.set(1, 2, 6);

    Udacity::Matrix<int> matrix71(3, 2);
    matrix71.set(0, 0, 7);
    matrix71.set(0, 1, 8);
    matrix71.set(1, 0, 9);
    matrix71.set(1, 1, 10);
    matrix71.set(2, 0, 11);
    matrix71.set(2, 1, 12);

    Udacity::Matrix<int> matrix72 = matrix70.multiply(matrix71);
    assert(matrix72.getRows() == 2);
    assert(matrix72.getCols() == 2);
    assert(matrix72.get(0, 0) == 58);
    assert(matrix72.get(0, 1) == 64);
    assert(matrix72.get(1, 0) == 139);
    assert(matrix72.get(1, 1) == 154);

    // Testing `multiplyParallel` function
    Udacity::Matrix<int> matrix73(2, 3);
    matrix73.set(0, 0, 1);
    matrix73.set(0, 1, 2);
    matrix73.set(0, 2, 3);
    matrix73.set(1, 0, 4);
    matrix73.set(1, 1, 5);
    matrix73.set(1, 2, 6);

    Udacity::Matrix<int> matrix74(3, 2);
    matrix74.set(0, 0, 7);
    matrix74.set(0, 1, 8);
    matrix74.set(1, 0, 9);
    matrix74.set(1, 1, 10);
    matrix74.set(2, 0, 11);
    matrix74.set(2, 1, 12);

    // Test multiplyParallel below with big matrices
    // Udacity::Matrix<int> matrix75 = matrix73.multiplyParallel(matrix74, 4);
    // assert(matrix75.getRows() == 2);
    // assert(matrix75.getCols() == 2);
    // assert(matrix75.get(0, 0) == 58);
    // assert(matrix75.get(0, 1) == 64);
    // assert(matrix75.get(1, 0) == 139);
    // assert(matrix75.get(1, 1) == 154);

    // Testing `inverse` function
    Udacity::Matrix<float> matrix76(2, 2);
    matrix76.set(0, 0, 3);
    matrix76.set(0, 1, 1);
    matrix76.set(1, 0, 2);
    matrix76.set(1, 1, 1);

    Udacity::Matrix<float> matrix77 = matrix76.inverse();
    assert(matrix77.getRows() == 2);
    assert(matrix77.getCols() == 2);
    assert(matrix77.get(0, 0) == 1.0f);
    assert(matrix77.get(0, 1) == -1.0f);
    assert(matrix77.get(1, 0) == -2.0f);
    assert(matrix77.get(1, 1) == 3.0f);

    // Testing `transpose` function
    Udacity::Matrix<float> matrix78(2, 3);
    matrix78.set(0, 0, 1);
    matrix78.set(0, 1, 2);
    matrix78.set(0, 2, 3);
    matrix78.set(1, 0, 4);
    matrix78.set(1, 1, 5);
    matrix78.set(1, 2, 6);

    Udacity::Matrix<float> matrix79 = matrix78.transpose();
    assert(matrix79.getRows() == 3);
    assert(matrix79.getCols() == 2);
    assert(matrix79.get(0, 0) == 1);
    assert(matrix79.get(1, 0) == 2);
    assert(matrix79.get(2, 0) == 3);
    assert(matrix79.get(0, 1) == 4);
    assert(matrix79.get(1, 1) == 5);
    assert(matrix79.get(2, 1) == 6);

    // Testing `determinant` function
    Udacity::Matrix<float> matrix80(2, 2);
    matrix80.set(0, 0, 3);
    matrix80.set(0, 1, 1);
    matrix80.set(1, 0, 2);
    matrix80.set(1, 1, 1);

    float determinant = matrix80.determinant();
    assert(determinant == 1.0f);

    // Testing `minor` function
    Udacity::Matrix<float> matrix81(3, 3);
    matrix81.set(0, 0, 3);
    matrix81.set(0, 1, 1);
    matrix81.set(0, 2, 2);
    matrix81.set(1, 0, 2);
    matrix81.set(1, 1, 4);
    matrix81.set(1, 2, 2);
    matrix81.set(2, 0, 1);
    matrix81.set(2, 1, 3);
    matrix81.set(2, 2, 1);

    Udacity::Matrix<float> matrix82 = matrix81.minor(1, 1);
    assert(matrix82.getRows() == 2);
    assert(matrix82.getCols() == 2);
    assert(matrix82.get(0, 0) == 3);
    assert(matrix82.get(0, 1) == 2);
    assert(matrix82.get(1, 0) == 1);
    assert(matrix82.get(1, 1) == 1);

    // Testing `adjoint` function
    Udacity::Matrix<int> matrix83(3, 3);
    matrix83.set(0, 0, 2);
    matrix83.set(0, 1, -1);
    matrix83.set(0, 2, 3);
    matrix83.set(1, 0, 0);
    matrix83.set(1, 1, 5);
    matrix83.set(1, 2, 2);
    matrix83.set(2, 0, 1);
    matrix83.set(2, 1, -1);
    matrix83.set(2, 2, -2);

    Udacity::Matrix<int> matrix84 = matrix83.adjoint();
    assert(matrix84.getRows() == 3);
    assert(matrix84.getCols() == 3);
    assert(matrix84.get(0, 0) == -8);
    assert(matrix84.get(0, 1) == -5);
    assert(matrix84.get(0, 2) == -17);
    assert(matrix84.get(1, 0) == 2);
    assert(matrix84.get(1, 1) == -7);
    assert(matrix84.get(1, 2) == -4);
    assert(matrix84.get(2, 0) == -5);
    assert(matrix84.get(2, 1) == 1);
    assert(matrix84.get(2, 2) == 10);

    // Testing resize function
    Udacity::Matrix<float> matrix85(3, 3);
    matrix85.set(0, 0, 3);
    matrix85.set(0, 1, 1);
    matrix85.set(0, 2, 2);
    matrix85.set(1, 0, 2);
    matrix85.set(1, 1, 4);
    matrix85.set(1, 2, 2);
    matrix85.set(2, 0, 1);
    matrix85.set(2, 1, 3);
    matrix85.set(2, 2, 1);

    matrix85.resize(4, 4);
    assert(matrix85.getRows() == 4);
    assert(matrix85.getCols() == 4);
    assert(matrix85.get(0, 0) == 3);
    assert(matrix85.get(0, 1) == 1);
    assert(matrix85.get(0, 2) == 2);
    assert(matrix85.get(1, 0) == 2);
    assert(matrix85.get(1, 1) == 4);
    assert(matrix85.get(1, 2) == 2);
    assert(matrix85.get(2, 0) == 1);
    assert(matrix85.get(2, 1) == 3);
    assert(matrix85.get(2, 2) == 1);
    assert(matrix85.get(3, 3) == 0);

    // Testing `print` function
    Udacity::Matrix<float> matrix86(3, 3);
    matrix86.set(0, 0, 3);
    matrix86.set(0, 1, 1);
    matrix86.set(0, 2, 2);
    matrix86.set(1, 0, 2);
    matrix86.set(1, 1, 4);
    matrix86.set(1, 2, 2);
    matrix86.set(2, 0, 1);
    matrix86.set(2, 1, 3);
    matrix86.set(2, 2, 1);

    matrix86.print();

    // Testing performance
    int numThreads = 4; // nProc

    Udacity::Matrix<int> matrix87(800, 800);
    Udacity::Matrix<int> matrix88(800, 800);
    matrix87.random();
    matrix88.random();

    auto start = std::chrono::high_resolution_clock::now();
    Udacity::Matrix matrix89 = matrix87 * matrix88;
    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    std::cout << "multiply(" << matrix89.getRows() << "," << matrix89.getCols() << ")[t]: " << std::to_string(elapsed) << "ms\n";

    start = std::chrono::high_resolution_clock::now();
    Udacity::Matrix matrix90 = matrix87.multiplyParallel(matrix88, numThreads);
    end = std::chrono::high_resolution_clock::now();
    elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    std::cout << "multiplyParallel(" << matrix90.getRows() << "," << matrix90.getCols() << ")[t]: " << std::to_string(elapsed) << "ms\n";
    assert(matrix89 == matrix90);

    std::cout << "All tests passed!" << std::endl;
}