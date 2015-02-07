//
//  Coin.h
//  AI-EVO-1
//
//  Created by Alex Reidy on 12/19/14.
//  Copyright (c) 2014 Alex Reidy. All rights reserved.
//

#ifndef __AI_EVO_1__Coin__
#define __AI_EVO_1__Coin__

#include "Entity.h"

class Coin : public Entity {
public:
    Coin(Vector2 position);
    void update();
};

#endif /* defined(__AI_EVO_1__Coin__) */
