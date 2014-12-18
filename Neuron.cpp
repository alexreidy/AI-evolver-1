//
//  Neuron.cpp
//  AI-EVO-1
//
//  Created by Alex Reidy on 12/15/14.
//  Copyright (c) 2014 Alex Reidy. All rights reserved.
//

#include "Neuron.h"

Neuron::Neuron(int threshold)
{
    this->threshold = threshold;
}

Neuron::Neuron()
{
    Neuron((int) rin(20));
}

Neuron::~Neuron() {}

void Neuron::setActionOnFire(Action onFire)
{
    this->onFire = onFire;
}

void Neuron::fire()
{
    for (Neuron *receiver : receivingNeurons) {
        receiver->receiveImpulse();
    }
    
    impulses = 0;
    onFire();
}

void Neuron::receiveImpulse()
{
    impulses++;
}

void Neuron::attemptFire()
{
    if (impulses > threshold)
        fire();
}

void Neuron::addReceivingNeuron(Neuron *n)
{
    receivingNeurons.push_back(n);
}