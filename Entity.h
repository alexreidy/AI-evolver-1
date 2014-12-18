//
//  Entity.h
//  AI-EVO-1
//
//  Created by Alex Reidy on 12/15/14.
//  Copyright (c) 2014 Alex Reidy. All rights reserved.
//

#ifndef __AI_EVO_1__Entity__
#define __AI_EVO_1__Entity__

#include <SFML/Graphics.hpp>
#include "util.h"

class Entity {
public:
    Entity(sf::Shape *shape, Vector2 position);
    Entity();
    
    ~Entity();
    
    void setPosition(Vector2 position);
    void setPosition(double x, double y);
    Vector2 getPosition() const;
    
    void move(double dx, double dy);
    void move(Vector2 offset);
    
    void setVelocity(Vector2 v);
    Vector2 getVelocity() const;
    
    virtual void update() = 0;

    const sf::Shape &getShape() const;
    void setShape(sf::Shape *shape);
    
protected:
    Vector2 velocity;
    
private:
    sf::Shape *shape = nullptr;
    
};

#endif /* defined(__AI_EVO_1__Entity__) */
