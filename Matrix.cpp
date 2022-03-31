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
                // cout << _mat[i][j] << endl;
                index++;
            }
        }
    }

    Matrix Matrix::operator+(const Matrix &otherMat)
    {

        return Matrix(operation(otherMat, 0, "+"), _row, _col);
    }

    Matrix Matrix::operator-(const Matrix &otherMat)
    {

        return Matrix(operation(otherMat, 0, "-"), _row, _col);
    }
    Matrix Matrix::operator-()
    {
        // first arg doesnt matter
        return Matrix(operation(*this, 0, "-@"), _row, _col);
    }

    Matrix Matrix::operator++(int)
    {
        operation(*this, 0, "a++");
        return *this;
    }

    Matrix &Matrix::operator++()
    {
        operation(*this, 0, "++a");
        return *this;
    }
    Matrix Matrix::operator--(int)
    {
        operation(*this, 0, "a--");
        return *this;
    }
    Matrix &Matrix::operator--()
    {
        operation(*this, 0, "--a");
        return *this;
    }
    Matrix operator*(const double scalar, const Matrix &Mat)
    {
        vector<double> new_vec;

        unsigned int index = 0;

        for (int i = 0; i < Mat._row; i++)
        {
            for (int j = 0; j < Mat._col; j++)
            {
                new_vec.push_back(scalar * Mat._mat.at(i).at(j));
                //    scalar *Mat._mat.at(i).at(j)
            }
        }

        return Matrix(new_vec, Mat._row, Mat._col);
    }

    Matrix &Matrix::operator*=(const double scalar)
    {

        operation(*this, scalar, "*=");
        return *this;
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

    vector<double> Matrix::operation(const Matrix &otherMat, int scalar, const string &oper)
    {
        vector<double> new_vec;

        unsigned int index = 0;
        // a+b
        if (oper == "+")
        {

            for (int i = 0; i < _row; i++)
            {
                for (int j = 0; j < _col; j++)
                {

                    double a = this->_mat.at(i).at(j);
                    double b = otherMat._mat.at(i).at(j);

                    new_vec.push_back(a + b);
                    index++;
                }
            }
        }
        // a-b
        else if (oper == "-")
        {
            for (int i = 0; i < _row; i++)
            {
                for (int j = 0; j < _col; j++)
                {
                    double a = this->_mat.at(i).at(j);
                    double b = otherMat._mat.at(i).at(j);

                    new_vec.push_back(a - b);
                    index++;
                }
            }
        }
        // -a
        else if (oper == "-@")
        {
            for (int i = 0; i < _row; i++)
            {
                for (int j = 0; j < _col; j++)
                {

                    new_vec.push_back((-1) * _mat[i][j]);
                    index++;
                }
            }
        }
        // a++
        else if (oper == "a++")
        {
            for (int i = 0; i < _row; i++)
            {
                for (int j = 0; j < _col; j++)
                {

                    _mat[i][j]++;
                }
            }
        }
        //+aa
        else if (oper == "++a")
        {
            for (int i = 0; i < _row; i++)
            {
                for (int j = 0; j < _col; j++)
                {

                    ++_mat[i][j];
                }
            }
        }
        // a--
        else if (oper == "a--")
        {
            for (int i = 0; i < _row; i++)
            {
                for (int j = 0; j < _col; j++)
                {

                    _mat[i][j]--;
                }
            }
        }
        //--a
        else if (oper == "--a")
        {
            for (int i = 0; i < _row; i++)
            {
                for (int j = 0; j < _col; j++)
                {

                    --_mat[i][j];
                }
            }
        }
        // a*=scalar
        else if (oper == "*=")
        {
            for (int i = 0; i < _row; i++)
            {
                for (int j = 0; j < _col; j++)
                {

                    _mat.at(i).at(j) *= scalar;
                }
            }
        }

        return new_vec;
    }
}