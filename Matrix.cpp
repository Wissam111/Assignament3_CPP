#include "Matrix.hpp"
// #include <iostream>
// using namespace std;

// using namespace zich;

namespace zich
{

    Matrix::Matrix(vector<double> vec, int row, int col)
    {
        this->_row = row;
        this->_col = col;

        unsigned int index = 0;
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++)
            {
                _mat[i][j] = vec[index];
                index++;
            }
        }
    }

    Matrix Matrix::operator+(const Matrix &otherMat)
    {

        return Matrix(operation(otherMat, 0, OPERATOR::plus), _row, _col);
    }

    Matrix Matrix::operator-(const Matrix &otherMat)
    {

        return Matrix(operation(otherMat, 0, OPERATOR::minus), _row, _col);
    }
    Matrix Matrix::operator-()
    {
        // first arg doesnt matter
        return Matrix(operation(*this, 0, OPERATOR::mutlNg1), _row, _col);
    }

    Matrix Matrix::operator++(int)
    {
        operation(*this, 0, plus1_right);
        return *this;
    }

    Matrix &Matrix::operator++()
    {
        operation(*this, 0, plus1_left);
        return *this;
    }
    Matrix Matrix::operator--(int)
    {
        operation(*this, 0, minus1_right);
        return *this;
    }
    Matrix &Matrix::operator--()
    {
        operation(*this, 0, minus1_left);
        return *this;
    }
    Matrix operator*(const double scalar, const Matrix &Mat)
    {

        Matrix m = Mat;

        return Matrix(m.operation(Mat, scalar, sc_mult), Mat._row, Mat._col);
    }

    Matrix &Matrix::operator*=(const double scalar)
    {

        operation(*this, scalar, sc_mutlEq);
        return *this;
    }
    Matrix &Matrix::operator+=(Matrix const &otherMat)
    {
        operation(otherMat, 0, plusEq);
        return *this;
    }

    bool operator==(const Matrix &mat1, const Matrix &mat2)
    {
        return compare(mat1, mat2, COMPARE::EQUAL);
    }
    bool operator!=(const Matrix &mat1, const Matrix &mat2)
    {
        return compare(mat1, mat2, COMPARE::NOTEQUAL);
    }
    bool operator>(const Matrix &mat1, const Matrix &mat2)
    {
        return compare(mat1, mat2, COMPARE::GREATER);
    }
    bool operator<(const Matrix &mat1, const Matrix &mat2)
    {
        return compare(mat1, mat2, COMPARE::SMALLER);
    }
    bool operator<=(const Matrix &mat1, const Matrix &mat2)
    {
        return compare(mat1, mat2, COMPARE::SMALLER_EQ);
    }
    bool operator>=(const Matrix &mat1, const Matrix &mat2)
    {
        return compare(mat1, mat2, COMPARE::GREATER_EQ);
    }
    ostream &operator<<(ostream &output, const Matrix &matrix)
    {
        string m;
        for (int i = 0; i < matrix._row; i++)
        {

            m += "[";
            for (int j = 0; j < matrix._col - 1; j++)
            {
                int a = matrix._mat.at(i).at(j);
                m += to_string(a);
                m += " ";
            }
            int a = matrix._mat.at(i).at(matrix._col - 1);
            m += to_string(a);
            m += "]\n";
        }
        output << m;

        return output;
    }

    vector<double> Matrix::operation(const Matrix &otherMat, int scalar, OPERATOR opr)
    {
        vector<double> new_vec;

        unsigned int index = 0;
        double a, b;

        for (int i = 0; i < _row; i++)
        {
            for (int j = 0; j < _col; j++)
            {

                switch (opr)
                {
                case plus:
                    a = this->_mat.at(i).at(j);
                    b = otherMat._mat.at(i).at(j);
                    new_vec.push_back(a + b);
                    index++;
                    break;

                case minus:
                    a = this->_mat.at(i).at(j);
                    b = otherMat._mat.at(i).at(j);
                    new_vec.push_back(a - b);
                    index++;
                    break;

                case mutlNg1:
                    new_vec.push_back((-1) * _mat[i][j]);
                    index++;
                    _mat[i][j] *= -1;
                    break;

                case minus1_left:
                    --_mat[i][j];
                    break;
                case minus1_right:
                    _mat[i][j]--;
                    break;

                case plus1_left:
                    ++_mat[i][j];
                    break;
                case plus1_right:
                    _mat[i][j]++;
                    break;

                case sc_mutlEq:
                    _mat.at(i).at(j) *= scalar;
                    break;
                case sc_mult:
                    new_vec.push_back(scalar * _mat.at(i).at(j));
                    break;

                case plusEq:
                    _mat.at(i).at(j) += otherMat._mat.at(i).at(j);

                default:
                    break;
                }
            }
        }

        return new_vec;
    }

    bool compare(const Matrix &mat1, const Matrix &mat2, COMPARE cmp)
    {
        bool ans;
        double m1, m2;
        for (int i = 0; i < mat1._row; i++)
        {
            for (int j = 0; j < mat1._col; j++)
            {
                m1 = mat1._mat.at(i).at(j);
                m2 = mat2._mat.at(i).at(j);

                switch (cmp)
                {
                case EQUAL:

                    if (m1 != m2)
                        return false;
                    break;

                case NOTEQUAL:
                    if (m1 != m2)
                        return true;
                    break;
                case GREATER:
                    if (sumMat(mat1) > sumMat(mat2))
                    {
                        return true;
                    }
                    return false;
                case SMALLER:
                    if (sumMat(mat1) < sumMat(mat2))
                    {
                        return true;
                    }
                    return false;
                case GREATER_EQ:
                    if ((sumMat(mat1) < sumMat(mat2)) || m1 != m2)
                    {
                        return false;
                    }
                    break;
                case SMALLER_EQ:
                    if ((sumMat(mat1) > sumMat(mat2)) || m1 != m2)
                    {
                        return false;
                    }
                    break;
                default:
                    break;
                }
            }
        }
        return true;
    }

    int sumMat(const Matrix &mat)
    {

        int sum = 0;
        for (int i = 0; i < mat._row; i++)
        {
            for (int j = 0; j < mat._col; j++)
            {
                sum += mat._mat.at(i).at(j);
            }
        }
        return sum;
    }
}