#pragma once

#include <vector>
#include "Neuron.h"

class NeuralNet
{
public:
	typedef std::vector<Neuron> Layer;

	NeuralNet(const std::vector<unsigned int> & topology);

	void setInputs(const std::vector<double> & inputs);
	static NeuralNet breed(NeuralNet &a, NeuralNet &b);

	std::vector<double> getOutput();
	~NeuralNet();
private:
	std::vector<Layer> _layers;
	std::vector<unsigned int> _topology;
};

