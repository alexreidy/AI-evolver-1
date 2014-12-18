#include <SFML/Graphics.hpp>
#include "util.h"
#include "Creature.h"
#include "Bullet.h"

const float WIDTH = 800, HEIGHT = 650;

Creature creature(Vector2{WIDTH / 2, HEIGHT / 2});

sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "AI evolution experiment #1");

std::vector<Bullet> bullets;

bool isOnScreen(Vector2 pos)
{
    return pos.x > 0 && pos.x < WIDTH &&
    pos.y > 0 && pos.y < HEIGHT;
}

Vector2 getMousePosition()
{
    auto pos = sf::Mouse::getPosition(window);
    return Vector2{(float) pos.x,
        (float) pos.y};
}

void initialize()
{
    window.setFramerateLimit(60);
    
    for (int i = 0; i < 30; i++) {
        bullets.push_back(Bullet(Vector2{rin(WIDTH), HEIGHT + 10}, Vector2{0, rin(10)+4}));
    }
}

void update()
{
    Vector2 mousepos = getMousePosition();
    creature.mpos = mousepos;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
        creature.setPosition(mousepos);
    
    if (rin(1) > 0.98) {
        for (Bullet b : bullets) {
            if (!isOnScreen(b.getPosition())) {
                b.setPosition(Vector2{rin(WIDTH), 1});
                break;
            }
        }
    }
    
    Vector2 closestBulletPos = Vector2{-500, -500};
    for (Bullet b : bullets) {
        if (isOnScreen(b.getPosition())) {
            b.update();
            
            if (calcDistanceBetween(b.getPosition(), creature.getPosition()) <
            calcDistanceBetween(closestBulletPos, creature.getPosition())) {
                closestBulletPos = b.getPosition();
            }
        }
    }
    
    creature.closestBulletPos = closestBulletPos;
    creature.update();
}

void render()
{
    window.clear(sf::Color::White);
    
    window.draw(creature.getShape());
    
    for (Bullet b : bullets) {
        window.draw(b.getShape());
    }
    
    window.display();
}

int main(int argc, char **argv)
{
    initialize();
    
    while (window.isOpen()) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            window.close();
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        update();
        render();
    }

    return EXIT_SUCCESS;
}
