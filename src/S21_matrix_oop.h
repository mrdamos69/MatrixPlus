#pragma once
#include <iostream>
#include <exception>
#include <math.h>

class S21Matrix
{
public:
    S21Matrix();
    S21Matrix(int rows, int cols);
    S21Matrix(const S21Matrix& other);
    S21Matrix(S21Matrix&& other);
    ~S21Matrix();
    bool eq_matrix(const S21Matrix& other);
    void sum_matrix(const S21Matrix& other);
    void sub_matrix(const S21Matrix& other);
    void mul_number(const double num);
    void mul_matrix(const S21Matrix& other);
    S21Matrix transpose();
    S21Matrix calc_complements();
    double determinant();
    S21Matrix inverse_matrix();

    S21Matrix operator + (const S21Matrix& other);
    S21Matrix operator - (const S21Matrix& other);
    S21Matrix operator * (const double& num);
    S21Matrix operator * (const S21Matrix& other);
    bool operator == (const S21Matrix& other);
    S21Matrix& operator = (const S21Matrix& other);
    S21Matrix& operator += (const S21Matrix& other);
    S21Matrix& operator -= (const S21Matrix& other);
    S21Matrix& operator *= (const double& num);
    S21Matrix& operator *= (const S21Matrix& other);
    double& operator () (const int rows, const int cols);

    void set_rows(int rows);
    int get_rows();
    void set_cols(int cols);
    int get_cols();

    void print_mtx();
    void gen_mtx();
    void gen_mtx_rev();
private:
    int rows;
    int cols;
    double** matrix;

};
