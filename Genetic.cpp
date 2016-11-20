#include "Genetic.h"
#include <assert.h>
#include "Neuron.h"
#include "NeuralNet.h"
#include "Random.h"

NeuralNet Genetic::breed(NeuralNet & a, NeuralNet & b)
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
		NeuralNet::Layer newLayer;
		child._layers.push_back(newLayer);

		//Average weights of two parents
		for (std::size_t j = 0; j < prevoiusLayerSize; ++j)
		{
			for (std::size_t k = 0; k < a._layers[i - 1].size(); ++k)
			{
				weights.push_back((a._layers[i - 1][j].getWeights()[k] + b._layers[i - 1][j].getWeights()[k]) / 2);
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

NeuralNet Genetic::mutate(NeuralNet a, double mutateRate)
{
	std::vector<double> weights;
	for (std::size_t i = 1; i < a._layers.size(); ++i)
	{
		for (std::size_t j = 0; j < a._layers[i].size(); ++j)
		{
			for (std::size_t k = 0; k < a._layers[i - 1].size(); ++k)
			{
				if (rand() % (int)(1 / mutateRate) == 0)
				{
					weights.push_back(Random::generate(a._layers[i][j].getWeights()[k]/2,a._layers[i][j].getWeights()[k] * 2));
				}
				else
				{
					weights.push_back(a._layers[i][j].getWeights()[k]);
				}
			}
			a._layers[i][j].setWeights(weights);
		}
	}
	return a;
}
