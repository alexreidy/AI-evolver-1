#include <SFML/Graphics.hpp>
#include "util.h"
#include "Creature.h"
#include "Bullet.h"

const float WIDTH = 800, HEIGHT = 650;

const Vector2 CENTER = Vector2{(float)WIDTH / 2, (float)HEIGHT / 2};

Creature creature(Vector2{WIDTH / 2, HEIGHT / 2});

sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "AI evolution experiment 1");

std::vector<Bullet> bullets;

bool canRender = false;

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
        bullets.push_back(Bullet(Vector2{rin(WIDTH), HEIGHT + 10}, Vector2{0, rin(2)+1}));
    }
}

int updatesSinceMutation = 0, generation = 1;

Brain brainBackup = Brain(0, 0);

int prevIQ = 0; // IQ = hp remaining after testing period

void update()
{
    Vector2 mousepos = getMousePosition();
    creature.mpos = mousepos;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::M))
        creature.setPosition(mousepos);
    
    if (!sf::Keyboard::isKeyPressed(sf::Keyboard::R) && rin(1) > 0.3) {
        for (Bullet b : bullets) {
            if (!isOnScreen(b.getPosition())) {
                if (rin(1) > 0.9) b.setPosition(Vector2{creature.getPosition().x, 1});
                else b.setPosition(Vector2{rin(WIDTH), 1});
                break;
            }
        }
    }
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::V))
        canRender = true;
    else canRender = false;
    
    Vector2 closestBulletPos = Vector2{-500, -500};
    for (Bullet b : bullets) {
        if (isOnScreen(b.getPosition())) {
            b.update();
            
            if (calcDistanceBetween(b.getPosition(), creature.getPosition()) <
            calcDistanceBetween(closestBulletPos, creature.getPosition())) {
                closestBulletPos = b.getPosition();
            }
            
            if (calcDistanceBetween(creature.getPosition(), b.getPosition()) < 7) {
                creature.changeHp(-1);
            }
        }
    }
    
    if (!isOnScreen(creature.getPosition()))
        creature.setPosition(CENTER);
    
    creature.closestBulletPos = closestBulletPos;
    creature.update();
    
    if (creature.getHp() < prevIQ || updatesSinceMutation == 5000) {
        std::cout << "Generation " << ++generation << std::endl;
        if (creature.getHp() < prevIQ) {
            // The last mutation made the creature dumber, so revert brain before mutating again
            creature.brain = brainBackup;
        } else {
            prevIQ = creature.getHp();
        }
        
        std::cout << "IQ to beat: " << prevIQ << std::endl;
        
        creature.changeHp(1000); // set to max hp, assuming max < 1000
        
        brainBackup = creature.brain;
        creature.brain.mutate();
        
        creature.setPosition(CENTER);
        
        updatesSinceMutation = 0;
    }
    
    updatesSinceMutation++;
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
        if (canRender) render();
    }

    return EXIT_SUCCESS;
}
