#pragma once
#include "NeuralNet.h"
class Genetic
{
public:
	friend class NeuralNet;
	static NeuralNet breed(NeuralNet &a, NeuralNet &b);
	static NeuralNet mutate(NeuralNet a, double mutateRate = 0.05);
};

