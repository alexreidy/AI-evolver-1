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

class Brain {
public:
    Brain(int numInputNeurons, int numOutputNeurons);
    ~Brain();
    
    void setActionForOutputNeuron(int index, Action action);
    
    void fireInputNeuron(int index);
        
    void fireExcitedNeurons();
    
private:
    std::vector<Neuron*> inputNeurons, outputNeurons;
    
    const int DEFAULT_NEURONS_PER_LAYER = 17;
    const int DEFAULT_LAYER_COUNT = 7;
    
    std::vector<std::vector<Neuron*>> layers;
    
};

#endif /* defined(__AI_EVO_1__Brain__) */