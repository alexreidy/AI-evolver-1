//
//  Bullet.cpp
//  AI-EVO-1
//
//  Created by Alex Reidy on 12/17/14.
//  Copyright (c) 2014 Alex Reidy. All rights reserved.
//

#include "Bullet.h"

Bullet::Bullet(Vector2 position, Vector2 velocity)
{
    sf::Shape *shape = new sf::RectangleShape(Vector2{5, 5});
    shape->setFillColor(sf::Color::Red);
    setShape(shape);
    
    setPosition(position);
    setVelocity(velocity);
}

Bullet::~Bullet() {}

void Bullet::update()
{
    move(getVelocity());
}