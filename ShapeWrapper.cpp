#include"ShapeWrapper.hpp"

ShapeWrapper::ShapeWrapper(): vertices(4)
{
    srand(time(0));
    int posX = rand() % 700 - 400, posY = rand() % 550 - 300;
    for(auto& x : vertices) x.color = sf::Color(rand() % 128 + 64, rand() % 128 + 64, rand() % 128 + 64);
    vertices[0].position = sf::Vector2f(posX, posY);
    vertices[1].position = sf::Vector2f(posX, posY + 50);
    vertices[2].position = sf::Vector2f(posX + 100, posY + 50);
    vertices[3].position = sf::Vector2f(posX + 100, posY);
}

void ShapeWrapper::transform(const Matrix& t)
{
    for(auto& v : vertices) v.position *= t;
}

void ShapeWrapper::rotate(const double angle)
{
    for(auto& v : vertices)
    {
        Matrix vertex(v.position);
        vertex.rotate(angle);
        v.position = sf::Vector2f(vertex.at(0, 0), vertex.at(0, 1));
    }
}

void ShapeWrapper::scale(const double x, const double y)
{
    for(auto& v : vertices)
    {
        Matrix vertex(v.position);
        vertex.scale(x, y);
        v.position = sf::Vector2f(vertex.at(0, 0), vertex.at(0, 1));
    }
}

void ShapeWrapper::translate(const double x, const double y)
{
    for(auto& v : vertices)
    {
        Matrix vertex(v.position);
        vertex.translate(x, y);
        v.position = sf::Vector2f(vertex.at(0, 0), vertex.at(0, 1));
    }
}

void ShapeWrapper::applyPerspective(const double x, const double y)
{
    for(auto& v : vertices)
    {
        Matrix vertex(v.position);
        vertex.applyPerspective(x, y);
        v.position = sf::Vector2f(vertex.at(0, 0), vertex.at(0, 1));
    }
}

void ShapeWrapper::draw(sf::RenderTarget& target) const
{
    target.draw(vertices.data(), vertices.size(), sf::PrimitiveType::TriangleFan);
}

std::vector<sf::Vertex>& ShapeWrapper::getVertices()
{
    return vertices;
}