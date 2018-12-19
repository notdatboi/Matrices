#include"Simulation.hpp"
#include<ctime>
#include<cstdlib>

Simulation::Simulation(): shapes(), transform(3, 3), window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "TEST"), axes(4, sf::Vertex(sf::Vector2f(0, 0), sf::Color(180, 70, 70))) 
{
    axes[0].position = sf::Vector2f(-1000, 0);
    axes[1].position = sf::Vector2f(1000, 0);
    axes[2].position = sf::Vector2f(0, -1000);
    axes[3].position = sf::Vector2f(0, 1000);
    sf::View view = window.getView();
    view.setCenter(0, 0);
    window.setView(view);
    transform.at(0, 0) = 1;
    transform.at(1, 1) = 1;
    transform.at(2, 2) = 1;
}

void Simulation::handleEvents(const sf::Event& event, double frameTime)
{
    if(event.type == sf::Event::KeyPressed)
    {
        if(event.key.code == sf::Keyboard::E)
        {
            for(auto& x : shapes)
                x->rotate(-3.1415926 * frameTime * 6);
            transform.rotate(-3.1415926 * frameTime * 6);
        }
        if(event.key.code == sf::Keyboard::Q)
        {
            for(auto& x : shapes)
                x->rotate(3.1415926 * frameTime * 6);
            transform.rotate(3.1415926 * frameTime * 6);
        }
        if(event.key.code == sf::Keyboard::W)
        {
            for(auto& x : shapes)
                x->translate(0, -frameTime * 5000);
            transform.translate(0, -frameTime * 5000);
        }
        if(event.key.code == sf::Keyboard::S)
        {
            for(auto& x : shapes)
                x->translate(0, frameTime * 5000);
            transform.translate(0, frameTime * 5000);
        }
        if(event.key.code == sf::Keyboard::A)
        {
            for(auto& x : shapes)
                x->translate(-frameTime * 5000, 0);
            transform.translate(-frameTime * 5000, 0);
        }
        if(event.key.code == sf::Keyboard::D)
        {
            for(auto& x : shapes)
                x->translate(frameTime * 5000, 0);
            transform.translate(frameTime * 5000, 0);
        }
        if(event.key.code == sf::Keyboard::Left)
        {
            for(auto& x : shapes)
                x->scale(1 + frameTime, 1);
            transform.scale(1 + frameTime, 1);
        }
        if(event.key.code == sf::Keyboard::Right)
        {
            for(auto& x : shapes)
                x->scale(1, 1 + frameTime);
            transform.scale(1, 1 + frameTime);
        }
        if(event.key.code == sf::Keyboard::Up)
        {
            for(auto& x : shapes)
                x->scale(1 + frameTime, 1 + frameTime);
            transform.scale(1 + frameTime, 1 + frameTime);
        }
        if(event.key.code == sf::Keyboard::Down)
        {
            for(auto& x : shapes)
                x->scale(1 - frameTime, 1 - frameTime);
            transform.scale(1 - frameTime, 1 - frameTime);
        }
        if(event.key.code == sf::Keyboard::M)
        {
            if(mode == Mode::applyTransform) mode = Mode::standard;
            else mode = Mode::applyTransform;
        }
    }
    else if(event.type == sf::Event::Closed) window.close();
    else if(event.type == sf::Event::MouseButtonPressed)
    {
        spawnShape(event.mouseButton.x, event.mouseButton.y);
    }
}

void Simulation::spawnShape(const double x, const double y)
{
    ShapeWrapper* shape = new ShapeWrapper(x, y);
    if(mode == Mode::applyTransform) shape->transform(transform);//10 32 18 40
    shapes.push_back(shape);
}

void Simulation::update(const sf::Time& frameTime)
{
}

void Simulation::draw()
{
    window.clear();
    window.draw(axes.data(), axes.size(), sf::Lines);
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