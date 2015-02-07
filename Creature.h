//
//  Creature.h
//  AI-EVO-1
//
//  Created by Alex Reidy on 12/15/14.
//  Copyright (c) 2014 Alex Reidy. All rights reserved.
//

#ifndef __AI_EVO_1__Creature__
#define __AI_EVO_1__Creature__

#include "Entity.h"
#include "Brain.h"

class Creature : public Entity {
public:
    Creature(Vector2 position);
    ~Creature();
    
    Brain brain = Brain(25, 8);
    
    void update();
    
    Vector2 mpos, closestBulletPos, closestCoinPos;
    
    int score = 0;
    
private:
};

#endif /* defined(__AI_EVO_1__Creature__) */
