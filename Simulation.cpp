#include"Simulation.hpp"
#include<ctime>
#include<cstdlib>

Simulation::Simulation(): shapes(), transform(), window(sf::VideoMode(800, 600), "TEST") 
{
    sf::View view = window.getView();
    view.setCenter(0, 0);
    window.setView(view);
}

void Simulation::handleEvents(const sf::Event& event, double frameTime)
{
    if(event.type == sf::Event::KeyPressed)
    {
        if(event.key.code == sf::Keyboard::F)
        {
            spawnShape();
        }
        if(event.key.code == sf::Keyboard::E)
        {
            for(auto& x : shapes)
                x->rotate(-3.1415926 * frameTime * 6);
        }
        if(event.key.code == sf::Keyboard::Q)
        {
            for(auto& x : shapes)
                x->rotate(3.1415926 * frameTime * 6);
        }
        if(event.key.code == sf::Keyboard::W)
        {
            for(auto& x : shapes)
                x->translate(0, -frameTime * 5000);
        }
        if(event.key.code == sf::Keyboard::S)
        {
            for(auto& x : shapes)
                x->translate(0, frameTime * 5000);
        }
        if(event.key.code == sf::Keyboard::A)
        {
            for(auto& x : shapes)
                x->translate(-frameTime * 5000, 0);
        }
        if(event.key.code == sf::Keyboard::D)
        {
            for(auto& x : shapes)
                x->translate(frameTime * 5000, 0);
        }
        if(event.key.code == sf::Keyboard::Left)
        {
            for(auto& x : shapes)
                x->scale(1 + frameTime, 1);
        }
        if(event.key.code == sf::Keyboard::Right)
        {
            for(auto& x : shapes)
                x->scale(1, 1 + frameTime);
        }
        if(event.key.code == sf::Keyboard::Up)
        {
            for(auto& x : shapes)
                x->scale(1 + frameTime, 1 + frameTime);
        }
        if(event.key.code == sf::Keyboard::Down)
        {
            for(auto& x : shapes)
                x->scale(1 - frameTime, 1 - frameTime);
        }
    }
    else if(event.type == sf::Event::Closed) window.close();
}

void Simulation::spawnShape()
{
    ShapeWrapper* shape = new ShapeWrapper();
    srand(time(0));
    shapes.push_back(shape);
}

void Simulation::update(const sf::Time& frameTime)
{
}

void Simulation::draw()
{
    window.clear();
    for(auto x : shapes)
    {
        x->draw(window);
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
        handleEvents(event, clock.getElapsedTime().asSeconds());
        timeSinceLastUpdate += clock.restart();
        while(timeSinceLastUpdate >= frameTime)
        {
            window.pollEvent(event);
            handleEvents(event, clock.getElapsedTime().asSeconds());
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