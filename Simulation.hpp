#ifndef SIMULATION_HPP
#define SIMULATION_HPP
#include"ShapeWrapper.hpp"

class Simulation
{
private:
    sf::RenderWindow window;
    const double fps = 60.f;
    const sf::Time frameTime = sf::seconds(1 / fps);
    std::vector<ShapeWrapper*> shapes;
    Matrix transform;
    void handleEvents(const sf::Event& event, double frameTime);
    void spawnShape();
    void update(const sf::Time& frameTime);
    void draw();
public:
    Simulation();
    void run();
    ~Simulation();
};

#endif