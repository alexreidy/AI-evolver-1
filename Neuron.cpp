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
    std::cout << threshold << std::endl;
    this->threshold = threshold;
}

Neuron::Neuron()
{
    Neuron((int) rin(6) + 1);
}

Neuron::~Neuron() {}

void Neuron::setActionOnFire(Action action)
{
    this->action = action;
}

void Neuron::fire()
{
    impulses = 0;
    action();
}

void Neuron::receiveImpulse()
{
    impulses++;
}

bool Neuron::tryFire()
{
    if (impulses > threshold) {
        fire();
        return true;
    }
    return false;
}

void Neuron::addRecipientNeuron(Cell address)
{
    recipientNeuronAddresses.push_back(address);
}

std::vector<Cell> Neuron::getRecipientNeuronAddresses() const
{
    return recipientNeuronAddresses;
}

void Neuron::removeRandomRecipient()
{
    if (recipientNeuronAddresses.size() == 0) return;
    recipientNeuronAddresses.erase(recipientNeuronAddresses.begin()+(int)rin(recipientNeuronAddresses.size()-1));
}

void Neuron::changeThreshold(int change)
{
    int nue = threshold + change;
    if (nue < 1) {
        threshold = 1;
        return;
    }
    threshold = nue;
}