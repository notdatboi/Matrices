#ifndef SHAPE_WRAPPER_HPP
#define SHAPE_WRAPPER_HPP
#include"Matrix.hpp"

class ShapeWrapper
{
private:
    std::vector<sf::Vertex> vertices;
public:
    ShapeWrapper();
    std::vector<sf::Vertex>& getVertices();
    void draw(sf::RenderTarget& target) const;
    void transform(const Matrix& t);
    void rotate(const double angle);            // in radians
    void scale(const double x, const double y);
    void translate(const double x, const double y);
    void applyPerspective(const double x, const double y);
};

#endif