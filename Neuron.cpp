#include "Neuron.h"
#include "NeuralNet.h"
#include <assert.h>
#include <iostream>

Neuron::Neuron()
{
}

void Neuron::setWeights(std::vector<double> weights)
{
	_weights = weights;
}

void Neuron::setInputs(std::vector<double> inputs)
{
	//assert((_weights.size() == _inputs.size()) && !(_inputs.size()==0));
	_inputs = inputs;
}

std::vector<double> Neuron::getWeights()
{
	return _weights;
}

double Neuron::output()
{
	double output = 0;
	for (std::size_t i = 0; i < _weights.size(); ++i)
	{
		output += _weights[i] * _inputs[i];
	}
	return output;
}

Neuron::~Neuron()
{
}
