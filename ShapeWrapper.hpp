#ifndef SHAPE_WRAPPER_HPP
#define SHAPE_WRAPPER_HPP
#include"Matrix.hpp"

const int SCREEN_HEIGHT = 600;
const int SCREEN_WIDTH = 800;

class ShapeWrapper
{
private:
    std::vector<sf::Vertex> vertices;
public:
    ShapeWrapper(const double posX = 0, const double posY = 0);
    std::vector<sf::Vertex>& getVertices();
    void draw(sf::RenderTarget& target) const;
    void transform(const Matrix& t);
    void rotate(const double angle);            // in radians
    void scale(const double x, const double y);
    void translate(const double x, const double y);
    void applyPerspective(const double x, const double y);
};

#endif