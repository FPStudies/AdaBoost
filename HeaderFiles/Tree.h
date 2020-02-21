#ifndef TREE_H
#define TREE_H
#include "Sample.h"
#include "Nodes.h"
#include <memory>

const static double EPS = 1e-7;

class Stump {
public:
	shortInt classify(const std::array<shortInt, Sample::ATTRIBUTES_NUMBER>& sample)
	{
		return root->classify(sample);
	}

	Stump(std::unique_ptr<Node>&& root, long double stumpWeight) : root(std::move(root)), stumpWeight(stumpWeight) {}

	/// Root node of the decision tree.
	std::unique_ptr<Node> root;
	long double stumpWeight;
};

class StumpTrain {
	shortInt cutoff[Sample::ATTRIBUTES_NUMBER];
	std::vector<Sample> samples;

private:
	// alias
	using Iter = typename std::vector<Sample>::iterator;

public:
	StumpTrain(std::vector<Sample>&& samples, shortInt* cutoff) : samples(std::move(samples)) {
		for (int i = 0; i < Sample::ATTRIBUTES_NUMBER; ++i) this->cutoff[i] = cutoff[i];
	}

	std::unique_ptr<Stump> train()
	{
		long double stumpVote = 0;
		auto node = train(samples.begin(), samples.end(), stumpVote);
		return std::unique_ptr<Stump>(new Stump(std::move(node), stumpVote));
	}

private:
	std::unique_ptr<Node> train(Iter start, Iter end, long double& stumpVote)
	{
		float Gini[Sample::ATTRIBUTES_NUMBER];
		float YesCorrect[Sample::ATTRIBUTES_NUMBER], YesIncorrect[Sample::ATTRIBUTES_NUMBER], NoCorrect[Sample::ATTRIBUTES_NUMBER], NoIncorrect[Sample::ATTRIBUTES_NUMBER];
		for (int i = 0; i < Sample::ATTRIBUTES_NUMBER; ++i)
		{
			YesCorrect[i] = 0.0; YesIncorrect[i] = 0.0; NoCorrect[i] = 0.0; NoIncorrect[i] = 0.0; Gini[i] = 0.0;
		}

		//count mistakes for every attribute
		for (auto it = start; it != end; ++it) {
			for (size_t i = 0; i < Sample::ATTRIBUTES_NUMBER; ++i) {
				if ((*it).attributes[i] > cutoff[i])
				{
					if ((*it).clazz == 0) YesIncorrect[i]+=(float)(*it).weight;
					else YesCorrect[i] += (float)(*it).weight;
				}
				else
				{
					if ((*it).clazz == 0) NoCorrect[i] += (float)(*it).weight;
					else NoIncorrect[i] += (float)(*it).weight;
				}
			}
		}

		//calculate the Gini index for every possible stump
		float all = YesCorrect[0] + YesIncorrect[0] + NoCorrect[0] + NoIncorrect[0];
		for (int i = 0; i < Sample::ATTRIBUTES_NUMBER; ++i)
		{
			Gini[i] = (((YesCorrect[i] + YesIncorrect[i]) / all) * HeartDiseaseData::countImpurity(YesCorrect[i], YesIncorrect[i])) + (((NoCorrect[i] + NoIncorrect[i]) / all) * HeartDiseaseData::countImpurity(NoCorrect[i], NoIncorrect[i]));
		}

		//find attribute with lowest Gini index
		std::pair<float, int> minGini;
		minGini.first = 100.0;
		minGini.second = 0;
		for (int i = 0; i < Sample::ATTRIBUTES_NUMBER; ++i)
		{
			if (Gini[i] < minGini.first) {
				minGini.first = Gini[i];
				minGini.second = i;
			}
		}
		int decidingAttribute = minGini.second;

		//calculate stump weight
		long double totalError = 0.0;
		
		for (auto it = start; it != end; ++it) {
				//incorrect classifications
			if ((((*it).attributes[decidingAttribute] > cutoff[decidingAttribute]) && (*it).clazz == 0) || \
				(((*it).attributes[decidingAttribute] <= cutoff[decidingAttribute]) && (*it).clazz == 1))
			{
				totalError += (*it).weight;
			}
		}
		long double stumpWeight = log((1 - totalError) / (totalError)) / 2;
		stumpVote = stumpWeight;

		//calculate new sample weights
		long double weightsum = 0.0;

		for (auto it = start; it != end; ++it) {
			//incorrect classifications
			if (((*it).attributes[decidingAttribute] > cutoff[decidingAttribute] && (*it).clazz == 0) || \
				((*it).attributes[decidingAttribute] <= cutoff[decidingAttribute] && (*it).clazz == 1))
			{
				weightsum+=(*it).newWeight(stumpWeight);
			}
			else
			{
				weightsum += (*it).newWeight(-stumpWeight);
			}
		}
		//normalize
		for (auto it = start; it != end; ++it) {
			(*it).weight /= weightsum;
		}

		return std::make_unique</*Inner*/Node>(decidingAttribute, cutoff[decidingAttribute]);
	}
};

#endif //TREE_H
