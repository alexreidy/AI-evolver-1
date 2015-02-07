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
    
    brain.setActionForOutputNeuron(0, [this]() {
        move(-3, 0);
    });
    
    brain.setActionForOutputNeuron(1, [this]() {
        move(0, -3);
    });
    
    brain.setActionForOutputNeuron(2, [this]() {
        move(3, 0);
    });
    
    brain.setActionForOutputNeuron(3, [this]() {
        move(0, 3);
    });
    
}

Creature::~Creature() {}

void Creature::update()
{
    if (closestBulletPos.x > 0) {
        if (closestBulletPos.x > getPosition().x)
            brain.fireInputNeuron(0);
        if (closestBulletPos.x < getPosition().x)
            brain.fireInputNeuron(1);
        if (closestBulletPos.y > getPosition().y)
            brain.fireInputNeuron(2);
        if (closestBulletPos.y < getPosition().y)
            brain.fireInputNeuron(3);
        
        if (calcDistanceBetween(getPosition(), closestBulletPos) < 30) {
            brain.fireInputNeuron(4);
        }
    }
    
    if (getPosition().x < 30) brain.fireInputNeuron(5);
    if (getPosition().x > 800-30) brain.fireInputNeuron(6);
    if (getPosition().y < 30) brain.fireInputNeuron(7);
    if (getPosition().y > 650-30) brain.fireInputNeuron(8);
    
    /*
    if (closestCoinPos.x > getPosition().x) brain.fireInputNeuron(9);
    if (closestCoinPos.x < getPosition().x) brain.fireInputNeuron(10);
    if (closestCoinPos.y > getPosition().y) brain.fireInputNeuron(11);
    if (closestCoinPos.y < getPosition().y) brain.fireInputNeuron(12);
    */
    brain.fireExcitedNeurons();
}