#include"Matrix.hpp"

Matrix::Matrix(int h, int w): matrix(h, std::vector<double>(w, 0)), height(h), width(w) {}

Matrix::Matrix(const std::vector<std::vector<double> >& vec): matrix(vec), height(vec.size()), width(vec[0].size()) {}

Matrix::Matrix(std::vector<std::vector<double> >&& vec): matrix(std::move(vec)), height(matrix.size()), width(matrix[0].size()) {}

double Matrix::at(int r, int c) const
{
    return matrix.at(r).at(c);
}

double& Matrix::at(int r, int c)
{
    return matrix.at(r).at(c);
}

Matrix Matrix::operator*(const Matrix& mult) const
{
    if(width != mult.height) throw std::logic_error("Not equal 1st matrix width and 2nd matrix height is not allowed.\n");
    Matrix result(height, mult.width);
    for(int i = 0; i < height; ++i)
    {
        for(int j = 0; j < mult.width; ++j)
        {
            double localResult = 0;
            for(int k = 0; k < width; ++k) localResult += this->at(i, k) * mult.at(k, j);
            result.at(i, j) = localResult;
        }
    }
    return result;
}

void Matrix::operator=(const Matrix& op)        // WARNING: heavy function, do not use without need
{
    matrix = std::vector<std::vector<double> >(op.height, std::vector<double>(op.width));
    height = op.height;
    width = op.width;
    for(int i = 0; i < height; ++i)
    {
        for(int j = 0; j < width; ++j)
        {
            matrix.at(i).at(j) = op.at(i, j);
        }
    }
}

void Matrix::operator*=(const Matrix& mult)     // WARNING: heavy function
{
    *(this) = *(this) * mult;
}

Matrix Matrix::operator*(const int x) const     // WARNING: heavy function
{
    Matrix result = *(this);
    for(int i = 0; i < result.height; ++i)
    {
        for(int j = 0; j < result.width; ++j)
        {
            result.at(i, j) *= x;
        }
    }
    return result;
}

void Matrix::operator*=(const int x)
{
    for(auto& v : matrix)
    {
        for(auto& i : v)
        {
            i *= x;
        }
    }
}

Matrix Matrix::operator+(const Matrix& plus) const
{
    if(height != plus.height || width != plus.width) throw std::logic_error("Matrices must have equal size.\n");
    Matrix result(height, width);
    for(int i = 0; i < height; ++i)
    {
        for(int j = 0; j < width; ++j)
        {
            result.at(i, j) = matrix.at(i).at(j) + plus.at(i, j);
        }
    }
    return result;
}

void Matrix::operator+=(const Matrix& plus)
{
    if(height != plus.height || width != plus.width) throw std::logic_error("Matrices must have equal size.\n");
    for(int i = 0; i < height; ++i)
    {
        for(int j = 0; j < width; ++j)
        {
            this->at(i, j) += plus.at(i, j);
        }
    }
}

void Matrix::rotate(const double angle)
{
    Matrix rotation(3, 3);
    rotation.at(2, 2) = 1;
    rotation.at(0, 0) = cos(angle);
    rotation.at(1, 1) = rotation.at(0, 0);
    rotation.at(0, 1) = sin(angle);
    rotation.at(1, 0) = -rotation.at(0, 1);
    (*(this)) *= rotation;
}

void Matrix::scale(const double x, const double y)
{
    Matrix s(3, 3);
    s.at(0, 0) = x;
    s.at(1, 1) = y;
    s.at(2, 2) = 1;
    (*(this)) *= s;
}

void Matrix::translate(const double x, const double y)
{
    Matrix translation(3, 3);
    translation.at(0, 0) = 1;
    translation.at(1, 1) = 1;
    translation.at(2, 2) = 1;
    translation.at(2, 0) = x;
    translation.at(2, 1) = y;
    (*(this)) *= translation;
}