#include"ShapeWrapper.hpp"

Matrix ShapeWrapper::fromVector2f(const sf::Vector2f& v) const
{
    Matrix res(1, 3);
    res.at(0, 0) = v.x;
    res.at(0, 1) = v.y;
    res.at(0, 2) = 1;
    return res;
}

Matrix ShapeWrapper::fromVector2f(const sf::Vector2f&& v) const
{
    Matrix res(1, 3);
    res.at(0, 0) = v.x;
    res.at(0, 1) = v.y;
    res.at(0, 2) = 1;
    return res;
}

ShapeWrapper::ShapeWrapper(): coords(4, Matrix(1, 3))
{
    shape = new sf::ConvexShape(4);
    shape->setPoint(0, sf::Vector2f(0, 50));
    coords[0].at(0, 1) = 50;
    coords[0].at(0, 2) = 1;
    shape->setPoint(1, sf::Vector2f(100, 50));
    coords[1].at(0, 0) = 100;
    coords[1].at(0, 1) = 50;
    coords[1].at(0, 2) = 1;
    shape->setPoint(2, sf::Vector2f(100, 0));
    coords[2].at(0, 0) = 100;
    coords[2].at(0, 2) = 1;
    shape->setPoint(3, sf::Vector2f(0, 0));
    coords[3].at(0, 2) = 1;
    shape->setFillColor(sf::Color(0, 127, 180));
}

void ShapeWrapper::transform(const Matrix& t)
{
    for(auto& x : coords) x *= t;
    int sz = coords.size();
    for(int i = 0; i < sz; ++i)
    {
        shape->setPoint(i, sf::Vector2f(coords[i].at(0, 0), coords[i].at(0, 1)));
    }
}

void ShapeWrapper::transformEveryPoint(const std::vector<Matrix>& t)
{
    if(t.size() != coords.size()) throw std::logic_error("You are trying to transform incorrect number of points.\n");
    int sz = t.size();
    for(int i = 0; i < sz; ++i)
    {
        coords.at(i) *= t.at(i);
    }
    for(int i = 0; i < sz; ++i)
    {
        shape->setPoint(i, sf::Vector2f(coords[i].at(0, 0), coords[i].at(0, 1)));
    }
}

sf::ConvexShape* ShapeWrapper::getShapePtr()
{
    return shape;
}

std::vector<Matrix>& ShapeWrapper::getShapeCoordsMatrix()
{
    return coords;
}

ShapeWrapper::~ShapeWrapper()
{
    delete shape;
}