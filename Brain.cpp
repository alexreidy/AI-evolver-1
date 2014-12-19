//
//  Brain.cpp
//  AI-EVO-1
//
//  Created by Alex Reidy on 12/15/14.
//  Copyright (c) 2014 Alex Reidy. All rights reserved.
//

#include "Brain.h"

Layer createNeuronLayer(int size, bool randomThresholds = true, int threshold = 1)
{
    Layer layer(size);
    
    for (int i = 0; i < size; i++) {
        if (randomThresholds) layer[i] = Neuron();
        else layer[i] = Neuron(threshold);
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
    
    
    for (int l = 0; l < DEFAULT_LAYER_COUNT + 1; l++) {
        std::cout << "Connecting layer " << l << std::endl;
        
        for (int a = 0; a < layers[l].size(); a++) {
            for (int b = 0; b < layers[l + 1].size(); b++) {
                if (rin(1) > 0.9) {
                    layers[l][a].addRecipientNeuron(Cell{l+1, b});
                }
            }
        }
    }
    
}

void Brain::setActionForOutputNeuron(int index, Action action)
{
    if (index < layers[layers.size()-1].size()) {
        layers[layers.size()-1][index].setActionOnFire(action);
    }
}

void Brain::deliverImpulsesFrom(Neuron n)
{
    for (Cell recipient : n.getRecipientNeuronAddresses()) {
        layers[recipient.row][recipient.col].receiveImpulse();
    }
}

void Brain::fireInputNeuron(int index)
{
    if (index < layers[0].size()) {
        layers[0][index].fire();
        deliverImpulsesFrom(layers[0][index]);
    }
}

void Brain::fireExcitedNeurons()
{
    for (Layer &layer : layers) {
        for (Neuron &n : layer) {
            if (n.tryFire()) {
                deliverImpulsesFrom(n);
            }
        }
    }
}

void Brain::mutate()
{
    for (Layer &layer : layers) {
        for (Neuron &n : layer) {
            if (rin(1) > 0.5) {
                if (rin(1) > 0.5) {
                    int l = (int)rin(layers.size()-1);
                    n.addRecipientNeuron(Cell{l, (int)rin(layers[l].size()-1)});
                }
                
                if (rin(1) > 0.5) {
                    n.removeRandomRecipient();
                }
                
                if (rin(1) > 0.5) {
                    n.changeThreshold((int)rsign(rin(5)));
                }
                
                break;
            }
        }
    }
}

Brain::~Brain() {}
