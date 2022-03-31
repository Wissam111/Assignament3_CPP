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

    enum OPERATOR
    {

        plus,         // a+b
        minus,        // a-b
        minus1_left,  //--a
        plus1_left,   //++a
        plus1_right,  // a++
        minus1_right, // a--
        mutlNg1,      //-a
        sc_mult,      // a*Scalar
        sc_mutlEq,    // a*=Scalar
        mult_mat,     // a*b
        plusEq,       // a+=b

    };
    enum COMPARE
    {

        EQUAL,
        NOTEQUAL,
        GREATER,
        SMALLER,
        GREATER_EQ,
        SMALLER_EQ,

    };

    class Matrix
    {

    private:
        map<int, map<int, double>> _mat;
        int _row, _col;

    public:
        Matrix(vector<double> vec, int row, int col);
        ~Matrix(){};
        // overloading output operator
        friend ostream &operator<<(ostream &output, const Matrix &matrix);
        // overloading input operator
        friend istream &operator>>(istream &input, Matrix &mat);

        vector<double> operation(const Matrix &otherMat, int scalar, OPERATOR opr);

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
        friend bool compare(const Matrix &mat1, const Matrix &mat2, COMPARE cmp);
        friend int sumMat(const Matrix &mat);
        friend bool operator==(const Matrix &mat1, const Matrix &mat2);
        friend bool operator!=(const Matrix &mat1, const Matrix &mat2);
        friend bool operator>(const Matrix &mat1, const Matrix &mat2);
        friend bool operator<(const Matrix &mat1, const Matrix &mat2);
        friend bool operator<=(const Matrix &mat1, const Matrix &mat2);
        friend bool operator>=(const Matrix &mat1, const Matrix &mat2);
    };
};
