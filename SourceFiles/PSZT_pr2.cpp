// PSZT_pr2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "../HeaderFiles/HeartDiseaseData.h"
#include "../HeaderFiles/Tree.h"
#include "../HeaderFiles/AdaBoost.h"


int main()
{
    std::cout << "Hello World!\n";

    HeartDiseaseData data;
    data.readData("Data/newCleveland.txt");
    data.coutData();

	//turn pointers to objects
	std::vector<Sample> Samples;
	Sample sample;

	for (int i = 0; i < data.dataSet->size(); ++i)
	{
		for (int j = 0; j < Sample::ATTRIBUTES_NUMBER; ++j)
		{
			sample.attributes[j] = (*((*(data.dataSet))[i])).values[j];
		}
		sample.clazz= (*((*(data.dataSet))[i])).values[Sample::ATTRIBUTES_NUMBER];
		sample.weight = 1 / (*(data.dataSet)).size();

		Samples.push_back(std::move(sample));
	}

	AdaBoost booster(std::move(Samples), data.cutoff);
	booster.train(20);


	int Correct=0, Incorrect=0;
	for (int i = 0; i < Samples.size(); ++i)
	{
		if (booster.classify(Samples[i]) == Samples[i].clazz) ++Correct;
		else ++Incorrect;
	}

	std::cout << "Correct: " << Correct << " \t" << "Incorrect: " << Incorrect << "\n";

	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
