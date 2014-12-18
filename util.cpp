//
//  util.cpp
//  AI-EVO-1
//
//  Created by Alex Reidy on 12/14/14.
//  Copyright (c) 2014 Alex Reidy. All rights reserved.
//

#include "util.h"

float rin(float range)
{
    std::random_device generator;
    std::uniform_real_distribution<double> distribution(0, range);
    return distribution(generator);
}

float rsign(float x)
{
    if (rin(1) >= 0.5) return x;
    return -x;
}

float calcDistanceBetween(Vector2 a, Vector2 b)
{
    return abs(hypotf(a.x - b.x, a.y - b.y));
}