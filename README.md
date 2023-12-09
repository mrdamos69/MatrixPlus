# s21_matrix+

## Matrix Operations Library in C++

This project implements a matrix operations library (`s21_matrix_oop.h`) in C++, providing a versatile set of functionalities for matrix manipulation. The library includes a `S21Matrix` class, implementing various matrix operations, constructors, destructors, and operator overloads.

## Matrix Operations

The `S21Matrix` class supports the following matrix operations:

| Operation | Description | Exceptional Situations |
| --- | --- | --- |
| `bool eq_matrix(const S21Matrix& other)` | Checks matrices for equality | |
| `void sum_matrix(const S21Matrix& other)` | Adds the second matrix to the current one | Different matrix dimensions |
| `void sub_matrix(const S21Matrix& other)` | Subtracts another matrix from the current one | Different matrix dimensions |
| `void mul_number(const double num)` | Multiplies the current matrix by a number | |
| `void mul_matrix(const S21Matrix& other)` | Multiplies the current matrix by the second matrix | Columns of the first matrix not equal to rows of the second matrix |
| `S21Matrix transpose()` | Creates a new transposed matrix from the current one | |
| `S21Matrix calc_complements()` | Calculates the algebraic addition matrix of the current one | Matrix is not square |
| `double determinant()` | Calculates and returns the determinant of the current matrix | Matrix is not square |
| `S21Matrix inverse_matrix()` | Calculates and returns the inverse matrix | Matrix determinant is 0 |

### Constructors and Destructors

The `S21Matrix` class includes the following constructors and destructors:

| Method | Description |
| --- | --- |
| `S21Matrix()` | Basic constructor, initializes a matrix of predefined dimensions |
| `S21Matrix(int rows, int cols)` | Parametrized constructor with the number of rows and columns |
| `S21Matrix(const S21Matrix& other)` | Copy constructor |
| `S21Matrix(S21Matrix&& other)` | Move constructor |
| `~S21Matrix()` | Destructor |

### Operator Overloads

The following operators are overloaded to support various matrix operations:

| Operator | Description | Exceptional Situations |
| --- | --- | --- |
| `+` | Matrix addition | Different matrix dimensions |
| `-` | Matrix subtraction | Different matrix dimensions |
| `*` | Matrix multiplication and matrix multiplication by a number | Columns of the first matrix not equal to rows of the second matrix |
| `==` | Checks for matrices equality (`eq_matrix`) | |
| `=` | Assignment of values from one matrix to another | |
| `+=` | Addition assignment (`sum_matrix`) | Different matrix dimensions |
| `-=` | Difference assignment (`sub_matrix`) | Different matrix dimensions |
| `*=` | Multiplication assignment (`mul_matrix`/`mul_number`) | Columns of the first matrix not equal to rows of the second matrix |
| `(int i, int j)` | Indexation by matrix elements (row, column) | Index outside the matrix |

## Implementation Details

- Developed in C++ using the C++17 standard with the GCC compiler.
- Code is organized within the `src` folder.
- Private fields `matrix`, `rows`, and `columns` are utilized for implementation.
- Access to private fields is achieved through accessor and mutator methods.
- Implemented as a static library with the `s21_matrix_oop.h` header file.
- Comprehensive unit tests provided using the GTest library.
- A Makefile is included for building the library and running tests, with targets `all`, `clean`, `test`, `s21_matrix_oop.a`.

## Usage

To build the library and run tests, use the provided Makefile with the following goals:

```bash
make all      # Build the library
make clean    # Clean the project files
make test     # Run tests
