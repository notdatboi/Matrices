#ifndef SHAPE_WRAPPER_HPP
#define SHAPE_WRAPPER_HPP
#include<SFML/Graphics.hpp>
#include"Matrix.hpp"

class ShapeWrapper
{
private:
    sf::ConvexShape* shape;
    std::vector<Matrix> coords;
    Matrix fromVector2f(const sf::Vector2f& v) const;
    Matrix fromVector2f(const sf::Vector2f&& v) const;
public:
    ShapeWrapper();
    sf::ConvexShape* getShapePtr();
    std::vector<Matrix>& getShapeCoordsMatrix();
    void transform(const Matrix& t);
    ~ShapeWrapper();
};

#endif