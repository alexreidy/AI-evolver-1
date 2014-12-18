//
//  Entity.cpp
//  AI-EVO-1
//
//  Created by Alex Reidy on 12/15/14.
//  Copyright (c) 2014 Alex Reidy. All rights reserved.
//

#include "Entity.h"

Entity::Entity(sf::Shape *shape, Vector2 position) : shape(shape)
{
    shape->setPosition(position);
}

Entity::Entity() {}

Entity::~Entity() {}

void Entity::setPosition(Vector2 position)
{
    if (shape != nullptr) shape->setPosition(position);
}

void Entity::setPosition(double x, double y)
{
    if (shape != nullptr) shape->setPosition(x, y);
}

Vector2 Entity::getPosition() const
{
    return shape->getPosition();
}

void Entity::move(double dx, double dy)
{
    shape->move(dx, dy);
}

void Entity::move(Vector2 offset)
{
    move(offset.x, offset.y);
}

void Entity::setVelocity(Vector2 v)
{
    velocity = v;
}

Vector2 Entity::getVelocity() const
{
    return velocity;
}

const sf::Shape &Entity::getShape() const
{
    return *shape;
}

void Entity::setShape(sf::Shape *shape)
{
    this->shape = shape;
}