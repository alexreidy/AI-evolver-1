//
//  Brain.h
//  AI-EVO-1
//
//  Created by Alex Reidy on 12/15/14.
//  Copyright (c) 2014 Alex Reidy. All rights reserved.
//

#ifndef __AI_EVO_1__Brain__
#define __AI_EVO_1__Brain__

#include "Neuron.h"

typedef std::vector<Neuron> Layer;

// Brain objects are designed to be copied

class Brain {
public:
    Brain(int numInputNeurons, int numOutputNeurons);
    ~Brain();
    
    void setActionForOutputNeuron(int index, Action action);
    
    void fireInputNeuron(int index);
    
    void fireExcitedNeurons();
    
    void mutate();
    
private:
    Layer inputNeurons, outputNeurons;
    
    static const int DEFAULT_NEURONS_PER_LAYER = 75;
    static const int DEFAULT_LAYER_COUNT = 3;
    
    std::vector<Layer> layers;
    
    void deliverImpulsesFrom(Neuron n);
};

#endif /* defined(__AI_EVO_1__Brain__) */