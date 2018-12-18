#ifndef MATRIX_HPP
#define MATRIX_HPP
#include<vector>
#include<stdexcept>
#include<cmath>
#include<SFML/Graphics.hpp>

class Matrix
{
private:
    std::vector<std::vector<double> > matrix;
public:
    int height, width;
    Matrix(int h = 3, int w = 3);
    Matrix(const sf::Vector2f& v);
    Matrix(const std::vector<std::vector<double> >& vec);
    Matrix(std::vector<std::vector<double> >&& vec);
    double at(int r, int c) const;
    double & at(int r, int c);
    Matrix operator*(const Matrix& mult) const;
    Matrix operator*(const double x) const;
    void operator=(const Matrix& op);
    void operator*=(const Matrix& mult);
    void operator*=(const double x);
    void operator/=(const double x);
    Matrix operator+(const Matrix& plus) const;
    void operator+=(const Matrix& plus);
    void rotate(const double angle);            // in radians
    void scale(const double x, const double y);
    void translate(const double x, const double y);
    void applyPerspective(const double x, const double y);
    //void applyPerspective(const double x, const double y, const double z);
};

void operator*=(sf::Vector2f& l, const Matrix& r);

#endif