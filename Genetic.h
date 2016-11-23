#pragma once
#include "NeuralNet.h"
#include "Defines.h"
class Genetic
{
public:
	struct genetic_nn
	{
		NeuralNet net;
		double eff;
		genetic_nn(NeuralNet a) : net(a) {}
		bool operator < (const genetic_nn& a) const
		{
			return (eff < a.eff);
		}
	};
	friend class NeuralNet;
	static NeuralNet breed(NeuralNet &a, NeuralNet &b);
	static NeuralNet mutate(NeuralNet a);
};

