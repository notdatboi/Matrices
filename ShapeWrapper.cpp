#include"ShapeWrapper.hpp"

ShapeWrapper::ShapeWrapper(const double posX, const double posY): vertices(4)
{
    srand(time(0));
    for(auto& x : vertices) x.color = sf::Color(rand() % 128 + 64, rand() % 128 + 64, rand() % 128 + 64);
    vertices[0].position = sf::Vector2f(posX - SCREEN_WIDTH / 2 - 50, posY - SCREEN_HEIGHT / 2 - 25);
    vertices[1].position = sf::Vector2f(posX - SCREEN_WIDTH / 2 - 50, posY + 25 - SCREEN_HEIGHT / 2);
    vertices[2].position = sf::Vector2f(posX + 50 - SCREEN_WIDTH / 2, posY + 25 - SCREEN_HEIGHT / 2);
    vertices[3].position = sf::Vector2f(posX + 50 - SCREEN_WIDTH / 2, posY - SCREEN_HEIGHT / 2 - 25);
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