#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>


void movementSystem(Registry& registry, float deltaTime) {
    registry.ForEach<Transform, Velocity>(
        [&] (Entity entity, Transform& transform, Velocity& velocity) {
            transform.x += velocity.vx * deltaTime;
            transform.y += velocity.vy * deltaTime;
        }
    );
}

void inputSystem(Registry& registry) {

    float const speed = 200.0f; //pixels per second

    registry.ForEach<Transform, Velocity>(
        [&] (Entity entity, Transform& transform, Velocity& velocity) {

            if (!registry.hasComponent<PlayerTag>(entity) || !registry.hasComponent<Input>(entity)) {
                return;
            }

            Input& input = registry.getComponent<Input>(entity);

            velocity.vx = 0;
            velocity.vy = 0;

            // Handle input for the entity
            if (input.up) {
                velocity.vy -= speed;
            }
            if (input.down) {
                velocity.vy += speed;
            }
            if (input.left) {
                velocity.vx -= speed;
            }
            if (input.right) {
                velocity.vx += speed;
            }

        }
    );
}

void renderSystem(Registry& registry, sf::RenderWindow& window){
    registry.ForEach<Sprite>(
        [&] (Entity entity, Sprite& sprite) {
            window.draw(sprite.shape);
        }
    );
}