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

void Neuron::inhibit()
{
    impulses--;
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

void Neuron::addNeuronToInhibit(Cell address)
{
    neuronsToInhibit.push_back(address);
}

std::vector<Cell> Neuron::getNeuronsToInhibit() const
{
    return neuronsToInhibit;
}

void Neuron::removeRandomRecipient()
{
    if (rin(1) > 0.5) {
        if (recipientNeuronAddresses.size() == 0)
            return;
        recipientNeuronAddresses.erase(
            recipientNeuronAddresses.begin() +
            (int)rin(recipientNeuronAddresses.size()-1)
        );
    } else {
        if (neuronsToInhibit.size() == 0) return;
        neuronsToInhibit.erase(neuronsToInhibit.begin() +
            (int)rin(neuronsToInhibit.size()-1));
    }
    
}

void Neuron::changeThreshold(int change)
{
    int nt = threshold + change;
    if (nt < 1) {
        threshold = 1;
        return;
    }
    threshold = nt;
}