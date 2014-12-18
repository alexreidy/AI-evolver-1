//
//  Creature.cpp
//  AI-EVO-1
//
//  Created by Alex Reidy on 12/15/14.
//  Copyright (c) 2014 Alex Reidy. All rights reserved.
//

#include "Creature.h"

Creature::Creature(Vector2 position)
{
    sf::Shape *shape = new sf::RectangleShape(Vector2{10, 10});
    shape->setFillColor(sf::Color::Blue);
    setShape(shape);
    
    setPosition(Vector2{450, 300});
    
    brain = new Brain(10, 4); // TODO make brain member var a value, not ptr
    
    brain->setActionForOutputNeuron(0, [this]() {
        move(-1, 0);
    });
    
    brain->setActionForOutputNeuron(1, [this]() {
        move(0, -1);
    });
    
    brain->setActionForOutputNeuron(0, [this]() {
        move(1, 0);
    });
    
    brain->setActionForOutputNeuron(0, [this]() {
        move(0, 1);
    });
    
}

Creature::~Creature() {}

void Creature::update()
{
    if (closestBulletPos.x > getPosition().x)
        brain->fireInputNeuron(0);
    if (closestBulletPos.x < getPosition().x)
        brain->fireInputNeuron(1);
    if (closestBulletPos.y > getPosition().y)
        brain->fireInputNeuron(2);
    if (closestBulletPos.y < getPosition().y)
        brain->fireInputNeuron(3);
    
    if (calcDistanceBetween(getPosition(), closestBulletPos) < 30) {
        brain->fireInputNeuron(4);
    }
    
    brain->fireExcitedNeurons();
}

void Creature::changeHp(int change)
{
    int chp = hp + change;
    if (chp > 0 && chp <= 100) {
        hp = chp;
    }
}

int Creature::getHp() const
{
    return hp;
}