#include "ecs/Entity.hpp"
#include "ecs/Registry.hpp"
#include "ecs/Components.hpp"
#include "ecs/Systems.hpp"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>



int main(){
    unsigned int windowSize = 800;
    sf::RenderWindow window(sf::VideoMode({windowSize, windowSize}), "Forest Fire Visual Model");

    Registry registry;
    Entity player = registry.create();
    registry.addComponent<Transform>(player, {0, 0, 0});
    registry.addComponent<Velocity>(player, {0, 0});
    registry.addComponent<Health>(player, {100});
    registry.addComponent<Sprite>(player, {sf::ConvexShape()});
    registry.addComponent<Input>(player, {false, false, false, false, false});
    registry.addComponent<Collision>(player, {10});
    registry.addComponent<PlayerTag>(player, {});



    //std::cout << "Created entity: " << player << std::endl;
    //registry.printRegistry();
    //registry.destroy(player);
    //std::cout << "Destroyed entity: " << player << std::endl;
    //registry.printRegistry();

    sf::Clock clock;

    while (window.isOpen())
    {  
        float dt = clock.restart().asSeconds();

        registry.ForEach<Input> (
            [&] (Entity entity, Input& input) {
                // This is just for testing, it will make the entity move in a circle
                input.up = sf::Keyboard::isKeyPressed(sf::Keyboard::W);
                input.down = sf::Keyboard::isKeyPressed(sf::Keyboard::S);
                input.left = sf::Keyboard::isKeyPressed(sf::Keyboard::A);
                input.right = sf::Keyboard::isKeyPressed(sf::Keyboard::D);
            }
        );

        inputSystem(registry);
        movementSystem(registry, dt);
        

        window.clear();

        renderSystem(registry, window);

        window.display();

        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }
    }

    
    return 0;
}