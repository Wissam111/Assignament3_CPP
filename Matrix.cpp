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

        return Matrix(operation(otherMat, "+"), _row, _col);
    }

    Matrix Matrix::operator-(const Matrix &otherMat)
    {

        return Matrix(operation(otherMat, "-"), _row, _col);
    }
    Matrix Matrix::operator-()
    {
        // first arg doesnt matter
        return Matrix(operation(*this, "-@"), _row, _col);
    }

    Matrix Matrix::operator++(int)
    {
        operation(*this, "_++");
        return *this;
    }

    Matrix &Matrix::operator++()
    {
        operation(*this, "_++");
        return *this;
    }
    Matrix Matrix::operator--(int)
    {
        operation(*this, "_--");
        return *this;
    }
    Matrix &Matrix::operator--()
    {
        operation(*this, "_--");
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

    vector<double> Matrix::operation(const Matrix &otherMat, const string &oper)
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
        else if (oper == "_++")
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
        else if (oper == "++_")
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
        else if (oper == "_--")
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
        else if (oper == "--_")
        {
            for (int i = 0; i < _row; i++)
            {
                for (int j = 0; j < _col; j++)
                {

                    --_mat[i][j];
                }
            }
        }

        return new_vec;
    }
}