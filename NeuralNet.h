#pragma once

#include <vector>
#include "Neuron.h"

class NeuralNet
{
public:
	friend class Genetic;

	typedef std::vector<Neuron> Layer;

	NeuralNet(const std::vector<unsigned int> & topology);

	void setInputs(const std::vector<double> & inputs);
	

	std::vector<double> getOutput();
	~NeuralNet();
protected:
	std::vector<Layer> _layers;
	std::vector<double> _inputs;
	std::vector<unsigned int> _topology;
};

