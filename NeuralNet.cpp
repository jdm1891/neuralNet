#include "NeuralNet.h"
#include <iostream>
#include <functional>
#include "Random.h"
#include <assert.h>
#include "Defines.h"


NeuralNet::NeuralNet(const std::vector<unsigned int>& topology) : _topology(topology)
{
	std::size_t prevoiusLayerSize = topology[0];

	//Start from the hidden layers - Input layers have no input weight!
	for (std::size_t i = 0; i < topology.size(); ++i)
	{
		//Declare the weights vector
		std::vector<double> weights;

		//Add a new layer
		Layer newLayer;
		_layers.push_back(newLayer);

		//Generate some random input weights
		for (std::size_t j = 0; j < prevoiusLayerSize; ++j)
		{
			weights.push_back(Random::generate(0, 1));
		}

		//Populate that layer with empty neurons
		for (std::size_t j = 0; j < topology[i]; ++j)
		{
			if (LOG)
			{
				std::cout << "Setting weights for neuron " << j + 1 << " of layer " << i + 1 << ": ";
			}
			Neuron newNeuron;
			if (i == 0)
			{
				//Set the weights of the input layer to 1!;
				std::fill(weights.begin(), weights.end(), 1);
				newNeuron.setWeights(weights);
			}
			else
			{
				newNeuron.setWeights(weights);
			}
			_layers[i].push_back(newNeuron);
		}

		//Get the layer size
		prevoiusLayerSize = topology[i];

		//Clear the weights vector for reuse
		weights.clear();
	}
}

void NeuralNet::setInputs(const std::vector<double> & inputs)
{
	assert(inputs.size()==_topology[0]);
	for (unsigned int i = 0; i < _layers[0].size(); ++i)
	{
		_layers[0][i].setInputs({ inputs[i] });
		if (LOG)
		{
			std::cout << "Neuron " << i+1 << " accepting input: " << inputs[i] << std::endl;
		}
	}
}

std::vector<double> NeuralNet::getOutput()
{
	for (std::size_t i = 1; i < _layers.size(); ++i)
	{
		for (std::size_t j = 0; j < _layers[i].size(); ++j)
		{
			std::vector<double> inputs;
			for (std::size_t j = 0; j < _layers[i-1].size(); ++j)
			{
				if (i = 1)
				{
					//Different calculating mechanism for the first layer
					inputs.push_back(_layers[i - 1][j].output(true));
				}
				else
				{
					inputs.push_back(_layers[i - 1][j].output());
				}
				
				if (LOG)
				{
					std::cout << "Neuron " << j + 1 << " of layer " << i << " is outputting " << inputs.back() << std::endl;
				}
			}
			_layers[i][j].setInputs(inputs);
			inputs.clear();
		}
	}
	std::vector<double> outputs;
	for (std::size_t i = 0; i < _layers.back().size(); ++i)
	{
		outputs.push_back(_layers.back()[i].output());
	}
	std::cout << outputs.size() << std::endl;
	return outputs;

}

NeuralNet::~NeuralNet()
{
}
