#include "Random.h"
#include <random>

double Random::generate(double lower, double higher)
{
	//create the random device
	static std::random_device rd;

	//Create a mt19937 generator
	static std::mt19937 gen(rd());

	//set the distribution
	static std::uniform_real_distribution<double> dis(lower, higher);

	return dis(gen);
}

int Random::generate_i(int lower, int higher)
{
	//create the random device
	static std::default_random_engine gen;
	static std::uniform_int_distribution<int> dis;
	return (dis(gen)%higher)+lower;
}