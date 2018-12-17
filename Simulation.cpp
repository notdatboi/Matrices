#include"Simulation.hpp"
#include<ctime>
#include<cstdlib>

Simulation::Simulation(): shapes(), transform(), window(sf::VideoMode(800, 600), "TEST") {}

void Simulation::handleEvents(const sf::Event& event)
{
    if(event.type == sf::Event::KeyPressed)
    {
        if(event.key.code == sf::Keyboard::F)
        {
            spawnShape();
        }
        else if(event.key.code == sf::Keyboard::W)
        {
            transform.at(0, 0) = (rand() % 10) / 5.f + 0.2;
            transform.at(1, 1) = (rand() % 10) / 5.f + 0.2;
            transform.at(2, 2) = 1;
            shapes[0]->transform(transform);
        }
    }
}

void Simulation::spawnShape()
{
    ShapeWrapper* shape = new ShapeWrapper();
    shapes.push_back(shape);
}

void Simulation::update(const sf::Time& frameTime)
{

}

//#include<iostream>

void Simulation::draw()
{
    window.clear();
    for(auto x : shapes)
    {
        window.draw((*(x->getShapePtr())));
    }
    window.display();
}

void Simulation::run()
{
    sf::Clock clock;
    sf::Time timeSinceLastUpdate;
    while(window.isOpen())
    {
        sf::Event event;
        window.pollEvent(event);
        handleEvents(event);
        timeSinceLastUpdate += clock.restart();
        while(timeSinceLastUpdate >= frameTime)
        {
            window.pollEvent(event);
            handleEvents(event);
            update(frameTime);
            timeSinceLastUpdate -= frameTime;
        }
        draw();
    }
}

Simulation::~Simulation()
{
    for(auto& x : shapes) delete x;
}