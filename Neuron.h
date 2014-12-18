//
//  Neuron.h
//  AI-EVO-1
//
//  Created by Alex Reidy on 12/15/14.
//  Copyright (c) 2014 Alex Reidy. All rights reserved.
//

#ifndef __AI_EVO_1__Neuron__
#define __AI_EVO_1__Neuron__

#include "util.h"

class Neuron {
public:
    Neuron(int threshold);
    Neuron();
    
    ~Neuron();
    
    void receiveImpulse();
    
    void fire();
    
    void setActionOnFire(Action onFire);
    
    void addReceivingNeuron(Neuron *n);
    
    void attemptFire();
    
private:
    std::vector<Neuron*> receivingNeurons;
    
    int threshold, impulses;
    
    Action onFire = []() {};
    
};

#endif /* defined(__AI_EVO_1__Neuron__) */