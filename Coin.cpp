//
//  Coin.cpp
//  AI-EVO-1
//
//  Created by Alex Reidy on 12/19/14.
//  Copyright (c) 2014 Alex Reidy. All rights reserved.
//

#include "Coin.h"

Coin::Coin(Vector2 position)
{
    sf::Shape *shape = new sf::RectangleShape(Vector2{5, 5});
    shape->setFillColor(sf::Color::Green);
    setShape(shape);
    
    setPosition(position);
}

void Coin::update() {}