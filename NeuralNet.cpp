#include "NeuralNet.h"
#include <iostream>
#include <functional>
#include "Random.h"
#include <assert.h>


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
			Neuron newNeuron;
			newNeuron.setWeights(weights);
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
		_layers[0][i].setInputs({ inputs });
	}
}

NeuralNet NeuralNet::breed(NeuralNet & a, NeuralNet & b)
{
	//Mismatched topologies not allowed!
	assert(a._topology == b._topology);

	//Create a child with parents topology
	NeuralNet child(a._topology);

	std::size_t prevoiusLayerSize = child._topology[0];

	//Start from the hidden layers - Input layers have no input weight!
	for (std::size_t i = 1; i < child._topology.size(); ++i)
	{
		//Declare the weights vector
		std::vector<double> weights;

		//Add a new layer
		Layer newLayer;
		child._layers.push_back(newLayer);

		//Average weights of two parents
		for (std::size_t j = 0; j < prevoiusLayerSize; ++j)
		{
			for (std::size_t k = 0; k < a._layers[i - 1].size(); ++k)
			{
				weights.push_back((a._layers[i-1][j].getWeights()[k] + b._layers[i-1][j].getWeights()[k]) / 2);
			}
		}

		//Populate that layer with empty neurons
		for (std::size_t j = 0; j < child._topology[i]; ++j)
		{
			Neuron newNeuron;
			newNeuron.setWeights(weights);
			child._layers[i].push_back(newNeuron);
		}

		//Get the layer size
		prevoiusLayerSize = child._topology[i];

		//Clear the weights vector for reuse
		weights.clear();
	}
	return child;
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
				inputs.push_back(_layers[i - 1][j].output());
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
	return outputs;

}

NeuralNet::~NeuralNet()
{
}
