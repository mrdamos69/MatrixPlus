#include "S21_matrix_oop.h"

S21Matrix::S21Matrix() {
    rows = 0;
    cols = 0;
    matrix = nullptr;
}

S21Matrix::S21Matrix(int rows, int cols) {
    this->rows = rows;
    this->cols = cols;
    matrix = new double* [rows];
    for (int i = 0; i < rows; i++)
        matrix[i] = new double[cols];
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            matrix[i][j] = 0;
}

S21Matrix::S21Matrix(const S21Matrix& other) {
    this->rows = other.rows;
    this->cols = other.cols;
    this->matrix = new double* [other.rows];
    for (int i = 0; i < this->rows; i++)
        this->matrix[i] = new double[other.cols];
    for (int i = 0; i < this->rows; i++)
        for (int j = 0; j < this->cols; j++)
            this->matrix[i][j] = other.matrix[i][j];
}

S21Matrix::S21Matrix(S21Matrix&& other) {
    for (int i = 0; i < rows; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
    *this = other;
    other.matrix = nullptr;
    other.rows = other.cols = 0;
}

S21Matrix::~S21Matrix() {
    for (int i = 0; i < rows; i++) {
        delete[]matrix[i];
    }
    delete[]matrix;
    matrix = nullptr;
    rows = 0;
    cols = 0;
}

bool S21Matrix::eq_matrix(const S21Matrix& other) {
    bool flag_status = true;
    if (other.rows != rows || other.cols != cols || other.rows <= 0 ||
        other.cols <= 0 || rows <= 0 || cols <= 0) {
        flag_status = false;
    } else {
        for (int i = 0; (i < rows) && flag_status; i++)
            for (int j = 0; (j < cols) && flag_status; j++)
                flag_status = (fabs(this->matrix[i][j] - other.matrix[i][j]) > 1e-07 ? false : true);
    }
    return flag_status;
}

void S21Matrix::sum_matrix(const S21Matrix& other) {
    if ((this->rows != other.rows) || (this->cols != other.cols))
        throw "the matrices are not equal!";
    if ((matrix != nullptr) && (other.matrix != nullptr) && (rows > 0)) {
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < cols; j++)
                matrix[i][j] = matrix[i][j] + other.matrix[i][j];
    }
}

void S21Matrix::sub_matrix(const S21Matrix& other) {
    if ((this->rows != other.rows) || (this->cols != other.cols))
        throw "the matrices are not equal!";
    if ((matrix != nullptr) && (other.matrix != nullptr) && (rows > 0)) {
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < cols; j++)
                matrix[i][j] = matrix[i][j] - other.matrix[i][j];
    }
}

void S21Matrix::mul_number(const double num) {
    if ((matrix != nullptr) && (rows > 0)) {
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < cols; j++)
                matrix[i][j] = matrix[i][j] * num;
    }
}

void S21Matrix::mul_matrix(const S21Matrix& other) {
    if (this->cols != other.rows)
        throw "columns is not equal to the number!";
    S21Matrix result(this->rows, other.cols);
    if ((matrix != nullptr) && (other.matrix != nullptr) && (rows > 0) && (cols > 0)) {
        for (int i = 0; (i < this->rows); i++)
            for (int j = 0; j < other.cols; j++)
                for (int k = 0; k < this->cols; k++)
                    result.matrix[i][j] += this->matrix[i][k] * other.matrix[k][j];
        for (int i = 0; i < this->rows; i++)
            delete[]matrix[i];
        delete[]matrix;
        this->rows = result.rows;
        this->cols = result.cols;
        this->matrix = new double* [result.rows];
        for (int i = 0; i < result.rows; i++)
            matrix[i] = new double[result.cols];
        *this = result;
    }
}

S21Matrix S21Matrix::transpose() {
    S21Matrix result(this->cols, this->rows);
    if ((this->matrix != nullptr) && ((this->rows) > 0) && (this->cols > 0)) {
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < cols; j++)
                result.matrix[j][i] = this->matrix[i][j];
    }
    for (int i = 0; i < this->rows; i++)
        delete[]matrix[i];
    delete[]matrix;
    this->rows = result.rows;
    this->cols = result.cols;
    matrix = new double* [result.rows];
    for (int i = 0; i < result.rows; i++)
        matrix[i] = new double[result.cols];
    *this = result;
    return *this;
}

S21Matrix S21Matrix::calc_complements() {
    if (this->rows != this->cols)
        throw "the matrix is not square";
    S21Matrix result(this->rows, this->cols);
    if (rows == cols) {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                S21Matrix temp_mtr(rows - 1, cols - 1);
                int count_i = 0, count_j = 0;
                for (int k = 0; k < rows; k++) {
                    if (k == i) continue;
                    for (int l = 0; l < cols; l++) {
                        if (l == j) continue;
                        temp_mtr.matrix[count_i][count_j] = matrix[k][l];
                        count_j++;
                    }
                    count_j = 0;
                    count_i++;
                }
                double determinant_value = temp_mtr.determinant();;
                determinant_value *= pow(-1, 2 + i + j);
                result.matrix[i][j] = determinant_value;
            }
        }
    }
    return result;
}

double S21Matrix::determinant() {
    if (this->rows != this->cols) {
        throw "the matrix is not square";
    }
    double result = 0;
    result = (rows == 1 ? matrix[0][0] : result);
    result = (rows == 2 ? matrix[0][0] * matrix[1][1] -
    matrix[0][1] * matrix[1][0] : result);
    if (rows != 1 && rows != 2) {
        result = 0;
        for (int i = 0; i < cols; i++) {
            S21Matrix temp_mtr(rows - 1, cols - 1);
            int count_i = 0, count_j = 0;
            for (int k = 0; k < rows; k++) {
                if (k == 0) continue;
                for (int l = 0; l < cols; l++) {
                    if (l == i) continue;
                    temp_mtr.matrix[count_i][count_j] = matrix[k][l];
                    count_j++;
                }
                count_j = 0;
                count_i++;
            }
            double tmp_det = temp_mtr.determinant();
            double tmp_res = pow(-1, 2 + i) * matrix[0][i] * tmp_det;
            result += tmp_res;
        }
    }
    return result;
}

S21Matrix S21Matrix::inverse_matrix() {
    if (this->determinant() == 0.0)
        throw "the determinant of the matrix is 0";
    S21Matrix result(this->rows, this->cols);
    S21Matrix tmp(this->rows, this->cols);
    double determ = this->determinant();
    if (fabs(determ) > 1e-7) {
        tmp = this->calc_complements();
        result = tmp.transpose();
        result.mul_number(1.0 / fabs(determ));
        for (int i = 0; i < result.rows; i++) {
            for (int j = 0; j < result.cols; j++) {
                result.matrix[i][j] *= -1;
            }
        }
    }
    return result;
}

void S21Matrix::gen_mtx() {
    double num = 1;
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++, num++)
            matrix[i][j] = num;
}

void S21Matrix::gen_mtx_rev() {
    double num = 32;
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++, num--)
            matrix[i][j] = num;
}

void S21Matrix::set_rows(int rows) {
    this->rows = rows;
}

int S21Matrix::get_rows() {
    return rows;
}

void S21Matrix::set_cols(int cols) {
    this->cols = cols;
}

int S21Matrix::get_cols() {
    return cols;
}


S21Matrix S21Matrix :: operator +(const S21Matrix& other) {
    if ((this->rows != other.rows) || (this->cols != other.cols))
        throw "the matrices are not equal!";
    S21Matrix result(this->rows, this->cols);
    if ((matrix != nullptr) && (other.matrix != nullptr) && (rows > 0)) {
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < cols; j++)
                result.matrix[i][j] = this->matrix[i][j] + other.matrix[i][j];
    }
    return result;
}

S21Matrix S21Matrix :: operator -(const S21Matrix& other) {
    if ((this->rows != other.rows) || (this->cols != other.cols))
        throw "the matrices are not equal!";
    S21Matrix result(this->rows, this->cols);
    if ((matrix != nullptr) && (other.matrix != nullptr) && (rows > 0)) {
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < cols; j++)
                result.matrix[i][j] = this->matrix[i][j] - other.matrix[i][j];
    }
    return result;
}

S21Matrix S21Matrix :: operator *(const double& num) {
    S21Matrix result(this->rows, this->cols);
    if ((matrix != nullptr) && (rows > 0)) {
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < cols; j++)
                result.matrix[i][j] = matrix[i][j] * num;
    }
    return result;
}

S21Matrix S21Matrix :: operator *(const S21Matrix& other) {
    if (this->cols != other.rows)
        throw "columns is not equal to the number!";
    S21Matrix result(this->rows, other.cols);
    if ((this->matrix != nullptr) && (other.matrix != nullptr) && (rows > 0) && (cols > 0)) {
        for (int i = 0; (i < this->rows); i++)
            for (int j = 0; j < other.cols; j++)
                for (int k = 0; k < this->cols; k++)
                    result.matrix[i][j] += this->matrix[i][k] * other.matrix[k][j];
    }
    return result;
}

S21Matrix& S21Matrix :: operator = (const S21Matrix& other) {
    if (this->matrix != nullptr) {
        for (int i = 0; i < this->rows; i++)
            delete[]matrix[i];
        delete[]matrix;
    }
    this->rows = other.rows;
    this->cols = other.cols;
    this->matrix = new double* [other.rows];
    for (int i = 0; i < this->rows; i++)
        this->matrix[i] = new double[other.cols];
        for (int i = 0; i < this->rows; i++)
            for (int j = 0; j < this->cols; j++)
                this->matrix[i][j] = other.matrix[i][j];
    return *this;
}

bool S21Matrix :: operator == (const S21Matrix& other) {
    bool flag_status = true;
    if (this->rows != other.rows || this->cols != other.cols || this->rows <= 0 ||
        this->cols <= 0 || other.rows <= 0 || other.cols <= 0) {
        flag_status = false;
    } else {
        for (int i = 0; (i < this->rows) && flag_status; i++)
            for (int j = 0; (j < this->cols) && flag_status; j++)
                flag_status = (fabs(this->matrix[i][j] - other.matrix[i][j]) > 1e-07 ? false : true);
    }
    return flag_status;
}

S21Matrix& S21Matrix :: operator += (const S21Matrix& other) {
    this->sum_matrix(other);
    return *this;
}

S21Matrix& S21Matrix :: operator -= (const S21Matrix& other) {
    this->sub_matrix(other);
    return *this;
}

S21Matrix& S21Matrix :: operator *= (const double& num) {
    this->mul_number(num);
    return *this;
}

S21Matrix& S21Matrix :: operator *= (const S21Matrix& other) {
    this->mul_matrix(other);
    return *this;
}

double& S21Matrix :: operator () (const int rows, const int cols) {
    if ((this->rows <= rows) || (this->cols <= cols))
        throw "index outside the matrix";
    return this->matrix[rows][cols];
}
