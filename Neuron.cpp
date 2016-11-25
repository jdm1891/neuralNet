#include "Neuron.h"
#include "NeuralNet.h"
#include <assert.h>
#include <iostream>
#include "Defines.h"

Neuron::Neuron()
{
}

void Neuron::setWeights(std::vector<double> weights)
{
	if (LOG)
	{
		for (const auto & a : weights)
		{
			std::cout << a << " ";
		}
		std::cout << std::endl;
	}
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

double Neuron::output(bool isFirstLayer)
{
	double output = 0;
	if (!isFirstLayer)
	{
		for (std::size_t i = 0; i < _weights.size(); ++i)
		{
			output += _weights[i] * _inputs[i];
		}
	}
	else
	{
		for (std::size_t i = 0; i < _weights.size(); ++i)
		{
			//Only one input per neuron on the first layer
			output += _weights[i] * _inputs[0];
		}
	}
	return output;
}

Neuron::~Neuron()
{
}
