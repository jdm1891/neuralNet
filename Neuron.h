#pragma once
#include <vector>


class Neuron
{
public:
	Neuron();
	void setWeights(std::vector<double> weights);
	void setInputs(std::vector<double> inputs);
	std::vector<double> getWeights();
	double output(bool isFirstLayer = false);
	~Neuron();
private:
	std::vector<double> _weights;
	std::vector<double> _inputs;
};

																																									