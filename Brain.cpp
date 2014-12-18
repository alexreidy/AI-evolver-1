//
//  Brain.cpp
//  AI-EVO-1
//
//  Created by Alex Reidy on 12/15/14.
//  Copyright (c) 2014 Alex Reidy. All rights reserved.
//

#include "Brain.h"

std::vector<Neuron*> createNeuronLayer(int size, bool randomThresholds = true, int threshold = 1)
{
    std::vector<Neuron*> layer(size);
    
    for (int i = 0; i < size; i++) {
        if (randomThresholds) layer.at(i) = new Neuron();
        else layer.at(i) = new Neuron(threshold);
    }
    
    return layer;
}

Brain::Brain(int numInputNeurons, int numOutputNeurons)
{
    inputNeurons = createNeuronLayer(numInputNeurons);
    outputNeurons = createNeuronLayer(numOutputNeurons);
    
    layers.push_back(inputNeurons);
    
    // Now add the internal neuron layers:
    for (int i = 0; i < DEFAULT_LAYER_COUNT; i++) {
        layers.push_back(createNeuronLayer(DEFAULT_NEURONS_PER_LAYER));
    }
    
    layers.push_back(outputNeurons);
    
    for (int i = 0; i < DEFAULT_LAYER_COUNT + 1; i++) {
        std::cout << "Connecting layer " << i << std::endl;
        for (Neuron *a : layers.at(i)) {
            for (Neuron *b : layers.at(i + 1)) { // TODO make efficient, make a certain number..
                if (rin(100.0) > 90) {
                    a->addReceivingNeuron(b);
                }
            }
        }
    }
    
}

void Brain::setActionForOutputNeuron(int index, Action action)
{
    if (index < outputNeurons.size()) {
        outputNeurons.at(index)->setActionOnFire(action);
    }
}

void Brain::fireInputNeuron(int index)
{
    if (index < inputNeurons.size())
        inputNeurons.at(index)->fire();
}

void Brain::fireExcitedNeurons() // TODO typedef Layer
{
    int l = 0;
    for (std::vector<Neuron*> layer : layers) {
        for (Neuron *n : layer) {
            n->attemptFire();
        }
        l++;
    }
}

Brain::~Brain() {}
