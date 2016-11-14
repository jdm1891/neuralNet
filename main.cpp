#include <iostream>
#include "NeuralNet.h"
#include <stdlib.h>
#include <algorithm>

#define GEN_SIZE 25
#define GEN_AMOUNT 3000
#define ELITE 1
int main()
{
	struct fitid
	{
		std::size_t id;
		double fitness;
		NeuralNet net;

		fitid(std::size_t k, double s, NeuralNet n) : id(k), fitness(s), net(n) {}

		bool operator < (const fitid& str) const
		{
			return (fitness < str.fitness);
		}
	};

	std::vector<NeuralNet> a;
	for (int m = 0; m < GEN_AMOUNT; m++)
	{
		std::vector <fitid> b;
		for (std::size_t i = 0; i < GEN_SIZE; ++i)
		{
			double rand_a = rand() % 20;
			double rand_b = rand() % 20;
			a.push_back(NeuralNet({ 2,2,1 }));
			a.back().setInputs({ rand_a, rand_b });
			double fitness = abs(rand_b + rand_a - a.back().getOutput().back());
			b.push_back(fitid(i, fitness, a.back()));
		}
		std::sort(b.begin(), b.end());
		std::vector<fitid> next;
		std::vector<NeuralNet> nextgen;
		for (const auto & item : b)
		{
			if (item.fitness < ELITE)
			{
				next.push_back(item);
				nextgen.push_back(item.net);
			}
		}
		if (next.size() == 0)
		{
			for (const auto & item : b)
			{
				if (item.fitness < ELITE*10)
				{
					next.push_back(item);
					nextgen.push_back(item.net);
				}
			}
		}
		int nextSize = next.size();
		for (std::size_t i = nextSize; i < GEN_SIZE; ++i)
		{
			NeuralNet & randoma = next[rand() % next.size()].net;
			NeuralNet & randomb = next[rand() % next.size()].net;
			nextgen.push_back(NeuralNet::breed(randoma, randomb));
		}
		a.clear();
		a = nextgen;
		if (m % 20 == 0)
		{
			std::cout << "Generation " << m << " has finished" << std::endl;
		}
	}
	for (int i = 0; i < 10; i++)
	{
		double rand_a = rand() % 20;
		double rand_b = rand() % 20;
		a.front().setInputs({ rand_a, rand_b });
		std::cout << "I think that " << rand_a << " + " << rand_b << " = " << round(a.front().getOutput()[0]) << std::endl;
	}
	system("pause");
	return 0;
}