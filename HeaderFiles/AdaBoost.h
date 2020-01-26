#pragma once
#include "Tree.h"


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
		if (classifiers.size() == 0) train(50);

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