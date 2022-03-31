#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <vector>
#include <string>
#include <map>
using namespace std;
using std::vector;
namespace zich
{

    class Matrix
    {

    private:
        // int _row, _col;
        // 1d vector to 2d vector
        // vector<vector<double>> _mat;
        // map<int, map<int, double>> _mat;
        // vector<double> _mat;

    public:
        map<int, map<int, double>> _mat;
        int _row, _col;
        // Matrix(vector<double> vec, int row, int col);
        Matrix(vector<double> vec, int row, int col);
        // Matrix();
        ~Matrix(){};
        // overloading output operator
        friend ostream &operator<<(ostream &output, const Matrix &matrix);
        // overloading input operator
        friend istream &operator>>(istream &input, Matrix &mat);

        vector<double> operation(const Matrix &otherMat, int scalar, const string &oper);
        Matrix operator+(const Matrix &otherMat);
        Matrix operator-(const Matrix &otherMat);
        Matrix operator-();
        // Matrix operator+();

        // Prefix decrement/increment operator.++mat
        Matrix &operator++();
        Matrix &operator--();
        // postfix decrement/increment operator. mat++
        Matrix operator++(int);
        Matrix operator--(int);

        friend Matrix operator*(const double scalar, const Matrix &mat);

        Matrix &operator*=(const double scalar);
        Matrix &operator+=(Matrix const &otherMat);
        Matrix operator*(Matrix const &otherMat);

        // Overload Comparison Operators

        friend bool operator==(const Matrix &mat1, const Matrix &mat2);
        friend bool operator!=(const Matrix &mat1, const Matrix &mat2);
        friend bool operator>(const Matrix &mat1, const Matrix &mat2);
        friend bool operator<(const Matrix &mat1, const Matrix &mat2);
        friend bool operator<=(const Matrix &mat1, const Matrix &mat2);
        friend bool operator>=(const Matrix &mat1, const Matrix &mat2);
    };
};
