#include <iostream>
#include "NeuralNet.h"
#include <stdlib.h>
#include <algorithm>
#include "Genetic.h"

#define GEN_SIZE 100
#define GEN_AMOUNT 10000
#define ELITE 3
int main()
{
	struct v
	{
		NeuralNet net;
		double eff;
		v(NeuralNet a) : net(a) {}
		bool operator < (const v& a) const
		{
			return (eff < a.eff);
		}
	};
	std::vector<v> a;
	for (int i = 0; i < 10; i++)
	{
		int random_a = rand() % 10;
		int random_b = rand() % 10;
		a.push_back(NeuralNet({ 2,1 }));
		a.back().net.setInputs({ (double)random_a, (double)random_b });
		a.back().eff = abs(random_a + random_b - a.back().net.getOutput().back());
	}
	for (int i = 0; i < 1000; i++)
	{
		int random_a = rand() % 10;
		int random_b = rand() % 10;
		for (int i = 1; i < a.size(); i++)
		{
			int random_a = rand() % 10;
			int random_b = rand() % 10;
			a[i-1].net.setInputs({ (double)random_a, (double)random_b });
			a[i-1].eff = abs(random_a + random_b - a[i-1].net.getOutput().back());
		}		
		std::sort(a.begin(), a.end());
		a.pop_back();
		a.push_back(Genetic::breed(a[0].net, a[1].net));
		for (int i = 2; i < a.size(); i++)
		{
			a[i].net = Genetic::mutate(a[i].net, 0.001f);
		}
		double mosteff = a.front().eff;
		std::cout << mosteff << std::endl;
	}
	std::cout << "Enter numbers to add:" << std::endl;
	double numa;
	double numb;
	std::cin >> numa >> numb;
	a.front().net.setInputs({ numa, numb });
	std::cout << a.front().net.getOutput()[0] << std::endl;
	system("pause");
	return 0;
}