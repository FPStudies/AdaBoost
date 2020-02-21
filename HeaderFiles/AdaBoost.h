#ifndef ADABOOST_H
#define ADABOOST_H
#include "Tree.h"
#include <algorithm>

const static int DEFAULT_STUMP_NUM = 20;


class AdaBoost {
	std::vector<std::unique_ptr<Stump>> classifiers;
	StumpTrain trainer;

public:

	AdaBoost(std::vector<Sample>&& samples, shortInt* cutoff) : trainer(std::move(samples), cutoff) {}

	void train(int trees)
	{
		for (int i=0; i<trees; ++i) classifiers.push_back(trainer.train());
	}

	shortInt classify(Sample& sample)
	{
		if (classifiers.size() == 0) train(DEFAULT_STUMP_NUM);

		long double Yes = 0.0, No=  0.0;
		for (int i = 0; i < classifiers.size(); ++i)
		{
			if (classifiers[i]->classify(sample.attributes) == 0) No += classifiers[i]->stumpWeight;
			else Yes += classifiers[i]->stumpWeight;
		}

		if (Yes >= No) return 1;
		return 0;
	}
};

long double crossValidateAda(int numberOfParts, std::vector<Sample> samples, shortInt* cutoffLine)
{
	std::random_shuffle(samples.begin(), samples.end());

	std::vector<AdaBoost> validators;
	std::vector<std::vector<Sample>> validationSamples;

	for (int i = 0; i < numberOfParts; ++i) validationSamples.push_back(std::vector<Sample>());

	//"split" samples into sets
	for (int i = 0; i < samples.size();)
	{
		for (int j = 0; j < numberOfParts && i < samples.size(); ++j)
		{
			validationSamples[j].push_back(samples[i]);
			++i;
		}
	}

	//cross validate
	std::vector<Sample> teachSample;
	long double correctGuess = 0.0, incorrectGuess = 0.0, sumq = 0.0;

	for (int i = 0; i < numberOfParts; ++i)
	{
		teachSample.clear();
		teachSample.reserve(samples.size());
		correctGuess = 0;
		incorrectGuess = 0;

		//prepare teaching set from sets apart from the current validation set
		for (int j = 0; j < numberOfParts; ++j)
		{
			if (j != i)
			{
				teachSample.insert(teachSample.end(), validationSamples[j].begin(), validationSamples[j].end());
			}
		}

		//make AdaBoost
		validators.push_back(AdaBoost(std::move(teachSample), cutoffLine));
		validators[i].train(DEFAULT_STUMP_NUM);

		//count mean error of validation part
		for (int j = 0; j < validationSamples[i].size(); ++j)
		{
			if (validationSamples[i][j].clazz == validators[i].classify(validationSamples[i][j])) ++correctGuess;
			else ++incorrectGuess;
		}
		sumq += incorrectGuess / (correctGuess + incorrectGuess);
	}

	//count mean error for whole classifier
	return (sumq / static_cast<long double>(numberOfParts));
}

#endif //ADABOOST_H
