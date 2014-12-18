//
//  util.h
//  AI-EVO-1
//
//  Created by Alex Reidy on 12/14/14.
//  Copyright (c) 2014 Alex Reidy. All rights reserved.
//


#ifndef __AI_EVO_1__util__
#define __AI_EVO_1__util__

#include <stdio.h>
#include <iostream>
#include <random>
#include <SFML/Graphics.hpp>

// Returns random double in given range
float rin(float range);

// Returns given double with a random sign
float rsign(float x);

// Action a = [this]() { f(x); };
typedef std::function<void(void)> Action;

typedef sf::Vector2<float> Vector2;

float calcDistanceBetween(Vector2 a, Vector2 b);

#endif /* defined(__AI_EVO_1__util__) */
