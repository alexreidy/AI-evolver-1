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
    
    void setActionOnFire(Action action);
    
    void addRecipientNeuron(Cell address);
    std::vector<Cell> getRecipientNeuronAddresses() const;
    
    // Returns true if it fires
    bool tryFire();
    
private:
    std::vector<Cell> recipientNeuronAddresses;
    
    int threshold = 2, impulses = 0;
    
    Action action = []() {};
    
};

#endif /* defined(__AI_EVO_1__Neuron__) */