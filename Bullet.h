//
//  Bullet.h
//  AI-EVO-1
//
//  Created by Alex Reidy on 12/17/14.
//  Copyright (c) 2014 Alex Reidy. All rights reserved.
//

#ifndef __AI_EVO_1__Bullet__
#define __AI_EVO_1__Bullet__

#include "Entity.h"

class Bullet : public Entity {
public:
    Bullet(Vector2 position, Vector2 velocity);
    
    ~Bullet();
    
    void update();
    
};

#endif /* defined(__AI_EVO_1__Bullet__) */
