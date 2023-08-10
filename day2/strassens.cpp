#include <vector>

using size_t = std::size_t;
template <typename T>
using vector2d = std::vector<std::vector<T>>;


template <typename T>
void check(const vector2d<T>& a, const vector2d<T>& b)
{
    size_t row_a = a.size();
    size_t col_a = a[0].size();
    size_t row_b = b.size();
    size_t col_b = b[0].size();
    if (row_a != col_a || row_b != col_b) {
        throw std::invalid_argument("matrix must be squaric");
    }
    if (row_a != row_b || col_a != col_b) {
        throw std::invalid_argument("matrix must be squari");
    }
    if ((row_a & (row_a) - 1) != 0) {
        throw std::invalid_argument("matrix size must be power of 2");
    }
    for (size_t i = 1; i < row_a; ++i) {
        if (a[i].size() != col_a || b[i].size() != col_b) {
            throw std::invalid_argument("uncorrect matrixes");
        }
    }
}


template <typename T>
void add_matrix(const vector2d<T>& a,const vector2d<T>& b, vector2d<T>& c)
{
    size_t row = a.size();
    size_t col = a[0].size();
    for (size_t i = 0; i < row; ++i) {
        for (size_t j = 0; j < col; ++j) {
            c[i][j] = a[i][j] + b[i][j];
        }
    }
}




template <typename T>
vector2d<T> strassens_mul(vector2d<T>& a, vector2d<T>& b)
{
    size_t size = a.size();
    size_t slice = size / 2;

    if (size == 1) {
        return {{a[0][0] * b[0][0]}};
    }

    vector2d<T> result(size, std::vector<T>(size, 0));

    std::vector<T> row(slice, 0);

    vector2d<T> a_00(slice, row);
    vector2d<T> a_01(slice, row);
    vector2d<T> a_10(slice, row);
    vector2d<T> a_11(slice, row);
    vector2d<T> b_00(slice, row);
    vector2d<T> b_01(slice, row);
    vector2d<T> b_10(slice, row);
    vector2d<T> b_11(slice, row);

    for (size_t i = 0; i < slice; ++i) {
        for (size_t j = 0; j < slice; ++j) {
            a_00[i][j] = a[i][j];
            a_01[i][j] = a[i][slice + j];
            a_10[i][j] = a[slice + i][j];
            a_11[i][j] = a[slice + i][slice + j];
            
            b_00[i][j] = b[i][j];
            b_01[i][j] = b[i][slice + j];
            b_10[i][j] = b[slice + i][j];
            b_11[i][j] = b[slice + i][slice + j];
        }
    }


    vector2d<T> result_00(slice, row);
    vector2d<T> result_01(slice, row);
    vector2d<T> result_10(slice, row);
    vector2d<T> result_11(slice, row);

    add_matrix(strassens_mul(a_00, b_00),
               strassens_mul(a_01, b_10),
               result_00);
    add_matrix(strassens_mul(a_00, b_01),
               strassens_mul(a_01, b_11),
               result_01);
    add_matrix(strassens_mul(a_10, b_00),
               strassens_mul(a_11, b_10),
               result_10);
    add_matrix(strassens_mul(a_10, b_01),
               strassens_mul(a_11, b_11),
               result_11);

    for (size_t i = 0; i < slice; ++i) {
        for (size_t j = 0; j < slice; ++j) {
            result[i][j] = result_00[i][j];
            result[i][slice + j] = result_01[i][j];
            result[slice + i][j] = result_10[i][j];
            result[slice + i][slice + j] = result_11[i][j];
        }
    }

    return result;
}




template <typename T>
vector2d<T> multiply_matrix(vector2d<T>& a, vector2d<T>& b)
{
    check(a, b);
    return strassens_mul(a, b);
}














