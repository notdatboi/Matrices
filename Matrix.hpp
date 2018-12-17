#ifndef MATRIX_HPP
#define MATRIX_HPP
#include<vector>
#include<stdexcept>

class Matrix
{
private:
    std::vector<std::vector<double> > matrix;
public:
    int height, width;
    Matrix(int h = 3, int w = 3);
    Matrix(const std::vector<std::vector<double> >& vec);
    Matrix(std::vector<std::vector<double> >&& vec);
    double at(int r, int c) const;
    double & at(int r, int c);
    Matrix operator*(const Matrix& mult) const;
    Matrix operator*(const int x) const;
    void operator=(const Matrix& op);
    void operator*=(const Matrix& mult);
    void operator*=(const int x);
    Matrix operator+(const Matrix& plus) const;
    void operator+=(const Matrix& plus);
};

#endif