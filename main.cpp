#include <SFML/Graphics.hpp>
#include "util.h"
#include "Creature.h"
#include "Bullet.h"
#include "Coin.h"

const float WIDTH = 800, HEIGHT = 650;

const Vector2 CENTER = Vector2{(float)WIDTH / 2, (float)HEIGHT / 2};

Creature creature(Vector2{WIDTH / 2, HEIGHT / 2});

sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "AI evolution experiment 1");

std::vector<Bullet> bullets;
std::vector<Coin> coins;

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
        bullets.push_back(Bullet(Vector2{rin(WIDTH), HEIGHT + 10}, Vector2{0, rin(5)+1}));
    }
    return;
    for (int i = 0; i < 100; i++) {
        coins.push_back(Coin(Vector2{rin(WIDTH), rin(HEIGHT)}));
    }
}

int updatesSinceMutation = 0, generation = 1;

Brain brainBackup = creature.brain;

int prevScore = -500000;

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
    
    /*
    if (isOnScreen(creature.getPosition())) {
        creature.brain.fireInputNeuron(850 + creature.getPosition().x);
    }
    */
    
    Vector2 closestBulletPos = Vector2{-500, -500};
    for (Bullet b : bullets) {
        if (isOnScreen(b.getPosition())) {
            b.update();
            
            //creature.brain.fireInputNeuron(20 + b.getPosition().x);
            
            if (calcDistanceBetween(b.getPosition(), creature.getPosition()) <
            calcDistanceBetween(closestBulletPos, creature.getPosition())) {
                closestBulletPos = b.getPosition();
            }
            
            if (calcDistanceBetween(creature.getPosition(), b.getPosition()) < 7) {
                creature.score--;
            }
        }
    }
    
    Vector2 closestCoinPos = Vector2{-500, 500};
    for (Coin &c : coins) {
        if (calcDistanceBetween(c.getPosition(), creature.getPosition()) <
        calcDistanceBetween(closestCoinPos, creature.getPosition())) {
            closestCoinPos = c.getPosition();
        }
        
        if (calcDistanceBetween(c.getPosition(), creature.getPosition()) < 7) {
            creature.score += 15;
            c.setPosition((int)rin(WIDTH), (int)rin(HEIGHT));
        }
    }
    
    creature.closestCoinPos = closestCoinPos;
    
    if (!isOnScreen(creature.getPosition())) {
        creature.score -= 15;
        creature.setPosition(CENTER);
    }
    
    creature.closestBulletPos = closestBulletPos;
    creature.update();
    
    if (creature.score < prevScore - 10 || updatesSinceMutation == 5000) {
        std::cout << "Score = " << creature.score << std::endl;
        std::cout << "Generation " << ++generation << std::endl;
        if (creature.score < prevScore) {
            // The last mutation made the creature dumber, so revert brain before mutating again
            creature.brain = brainBackup;
        } else {
            prevScore = creature.score;
        }
        
        std::cout << "Score to beat: " << prevScore << std::endl;
        
        creature.score = 0;
        
        brainBackup = creature.brain;
        if (rin(1) > 0.8) creature.brain.mutate();
        
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
    
    for (Coin c : coins)
        window.draw(c.getShape());
    
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
