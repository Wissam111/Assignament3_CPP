#include "Matrix.hpp"

namespace zich
{

    Matrix::Matrix(vector<double> vec, int row, int col)
    {
        if (row <= 0 || col <= 0)
        {
            throw invalid_argument("numbers should be postives");
        }

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

    /*
     * @brief  overloading a+b , a-b , --a , ++a , a++ , a--
     *         -a , a*Scalar , a*=Scalar , a*b , a+=b operators
     */

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
    Matrix Matrix::operator+()
    {

        return Matrix(operation(*this, 0, OPERATOR::plusUnary), _row, _col);
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

    Matrix Matrix::operator*(Matrix const &otherMat)
    {

        return Matrix(operation(otherMat, 0, OPERATOR::mult_mat), _row, otherMat._col);
    }

    /*
     * @brief  overloading compare operators
     *         == , != , > ,<, >= , <=
     */

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

    /*
     * @brief  overloading input/output
     */
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

    istream &operator>>(istream &input, Matrix &mat);

    /*
     * @brief fucntion that handle +,- , etc operators
     */
    vector<double> Matrix::operation(const Matrix &otherMat, double scalar, OPERATOR opr)
    {
        if (!checkValidation(*this, otherMat, opr))
        {
            throw invalid_argument("invalid operation on the matrix");
        }
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
                    break;

                case mult_mat:
                    return mulMat(*this, otherMat);

                case plusUnary:
                    new_vec.push_back(_mat[i][j]);
                    index++;
                    break;

                default:
                    break;
                }
            }
        }

        return new_vec;
    }

    /*
     * @brief fucntion that handle compare  operators
     */
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
                    if ((sumMat(mat1) >= sumMat(mat2)))
                    {
                        return true;
                    }
                    return false;
                case SMALLER_EQ:
                    if ((sumMat(mat1) <= sumMat(mat2)))
                    {
                        return true;
                    }
                    return false;
                default:
                    break;
                }
            }
        }
        return true;
    }

    /*
     * @brief calculate the sum of matrix
     */
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

    /*
     * @brief calculate the multiplication of two matrix
     */
    vector<double> mulMat(const Matrix &mat1, const Matrix &mat2)
    {

        vector<double> result;

        // n*m m*k => n*k
        if (mat2._row != mat1._col)
        {
            throw invalid_argument("invalid operation on the matrix");
        }

        for (int i = 0; i < mat1._row; i++)
        {
            for (int j = 0; j < mat2._col; j++)
            {

                int temp = 0;
                for (int k = 0; k < mat2._row; k++)
                {

                    temp += mat1._mat.at(i).at(k) * mat2._mat.at(k).at(j);
                }

                result.push_back(temp);
            }
        }

        return result;
    }
    /*
     * @brief check valdation of an input
     */
    bool checkValidation(const Matrix &mat1, const Matrix &mat2, OPERATOR opr)
    { // n*m m*k
        if ((opr == plus || opr == minus || opr == plusEq) && ((mat1._col != mat2._col) || (mat1._row != mat2._row)))
        {
            return false;
        }

        if (opr == mult_mat && mat1._col != mat2._row)
        {
            return false;
        }

        return true;
    }

}