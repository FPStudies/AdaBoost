// PSZT_pr2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "../HeaderFiles/Tree.h"
#include "../HeaderFiles/HeartDiseaseData.h"
#include "../HeaderFiles/AdaBoost.h"


int main(int argc, char* argv[])
{
	if (argc != 3)
	{
		std::cout << "Wrong arguments. Usage: AdaBoost TeachSetFile ValidateSetFile\n";
		return 1;
	}

    HeartDiseaseData dataTeach, dataValidate;

	// read data from file
    dataTeach.readData(argv[1]);
	dataValidate.readData(argv[2]);

	if (!dataTeach.isSet() || !dataValidate.isSet())
	{
		std::cout << "Could not load data.\n";
		return 1;
	}


	//turn pointers to objects
	std::vector<Sample> teachSamples, validateSamples;
	Sample sample;

	// copy data
	for (int i = 0; i < dataTeach.dataSet->size(); ++i)
	{
		for (int j = 0; j < Sample::ATTRIBUTES_NUMBER; ++j)
		{
			sample.attributes[j] = (*((*(dataTeach.dataSet))[i])).values[j];
		}
		sample.clazz= (*((*(dataTeach.dataSet))[i])).values[Sample::ATTRIBUTES_NUMBER];

		// at the beginning all of the samples have the same weight
		sample.weight = 1.0 / static_cast<long double>((*(dataTeach.dataSet)).size()); 

		teachSamples.push_back(std::move(sample));
	}

	for (int i = 0; i < dataValidate.dataSet->size(); ++i)
	{
		for (int j = 0; j < Sample::ATTRIBUTES_NUMBER; ++j)
		{
			sample.attributes[j] = (*((*(dataValidate.dataSet))[i])).values[j];
		}
		sample.clazz = (*((*(dataValidate.dataSet))[i])).values[Sample::ATTRIBUTES_NUMBER];

		validateSamples.push_back(std::move(sample));
	}



	long double d = crossValidateAda(5, teachSamples, dataTeach.cutoffLine);
	
	AdaBoost classifier(std::move(teachSamples), dataTeach.cutoffLine);

	classifier.train(20);

	int correct=0, incorrect=0;
	shortInt clazz=0, guess=0;

	for (int i = 0; i < validateSamples.size(); ++i)
	{
		clazz = validateSamples[i].clazz;
		guess = classifier.classify(validateSamples[i]);

		std::cout << validateSamples[i] << "- \t" << guess;

		if (clazz == guess) ++correct;
		else
		{
			std::cout << "\t#";
			++incorrect;
		}
		std::cout<<"\n";
	}

	std::cout << "\nCorrect classifications: " << correct << "\tIncorrect classifications: " << incorrect << "\n";
	std::cout << "Mean error: " << d << "\n";

	return 0;
}
