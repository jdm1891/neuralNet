#include <iostream>
#include "NeuralNet.h"
#include <stdlib.h>
#include <algorithm>
#include "Genetic.h"
#include "Random.h"

int main()
{
	std::vector<Genetic::genetic_nn> vec;

	for (int creature = 0; creature < GEN_SIZE; ++creature)
	{
		vec.push_back(Genetic::genetic_nn(NeuralNet({ 2,1 })));
	}

	for (int generation = 0; generation < GEN_AMOUNT; ++generation)
	{
		for (int creature = 0; creature < GEN_SIZE; ++creature)
		{
			std::cout << creature << " " << vec.size() << std::endl;
			double first_random = Random::generate_i(1, 100);
			double second_random = Random::generate_i(1, 100);
			vec[creature].net.setInputs({ first_random, second_random });
			double output = vec[creature].net.getOutput()[0];
			std::cout << output << std::endl;
			vec[creature].eff = abs(0 - (first_random + second_random));
		}

		std::sort(vec.begin(), vec.end());

		for (int breed = 0; breed < int(GEN_SIZE / 10); ++breed)
		{
			vec.insert(vec.begin(), Genetic::genetic_nn(Genetic::breed(vec[breed].net, vec[breed + 1].net)));
		}

		for (int kill = vec.size(); kill > GEN_SIZE; --kill)
		{
			vec.pop_back();
		}
		
		for (int mutate = 0; mutate < vec.size(); ++mutate)
		{
			Genetic::mutate(vec[mutate].net);
		}
		if (generation % 50 == 0)
		{
			std::cout << "On generation " << generation << " of " << GEN_AMOUNT << std::endl;
		}
		std::cout << vec.size() << std::endl;
	}
	std::cout << "Best adding machine's efficiency: " << vec.front().eff << std::endl;
	system("pause");
}