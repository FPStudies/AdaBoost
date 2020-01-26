#pragma once
#include "Sample.h"
#include "Nodes.h"

const static float EPS = 1e-7;

class ID3 {
public:
	shortInt classify(const std::array<shortInt, Sample::ATTRIBUTES_NUMBER>& sample)
	{
		return root->classify(sample);
	}

	void print(std::ostream& os)
	{
		root->print(os, 0);
	}

	ID3(std::unique_ptr<Node>&& root) : root(std::move(root)) {}

	/// Root node of the decision tree.
	std::unique_ptr<Node> root;
};

class ID3Train {
	

private:
	// Some shorthand aliases.
	using Iter = typename std::vector<Sample>::iterator;

public:
	ID3Train(std::vector<Sample>&& samples) : samples(std::move(samples)) {}

	std::unique_ptr<ID3> train()
	{
		return std::unique_ptr<ID3>(new ID3(train(samples.begin(), samples.end())));
	}

private:
	std::unique_ptr<Node> train(Iter start, Iter end)
	{
		auto ig = std::make_pair(0, std::numeric_limits<float>::min());
		std::unordered_map<shortInt, size_t> clazzes;
		shortInt maxClazz;

		// For each attribute/value pair, compute how many items fall into that category.
		std::array<std::unordered_map<shortInt, std::unordered_map<shortInt, size_t>>, Sample::ATTRIBUTES_NUMBER> count;
		for (auto it = start; it != end; ++it) {
			for (size_t i = 0; i < Sample::ATTRIBUTES_NUMBER; ++i) {
				count[i][it->attributes[i]][it->clazz]++;
			}
			clazzes[it->clazz]++;
		}

		// Compute the entropy of the current set.
		auto entropy = 0.0f;
		auto total = end - start;
		for (auto clazz : clazzes) {
		auto p = clazz.second / (float)total;
		entropy -= p * log(p) / log(2.0f);

		if (clazz.second > clazzes[maxClazz]) {
			maxClazz = clazz.first;
			}
		}

		// If set is all classified, return leaf node.
		if (abs(entropy) <= EPS) {
			return std::make_unique<TerminalNode>(start->clazz);
		}

		// Compute the information gain on all possible splits.
		for (size_t i = 0; i < Sample::ATTRIBUTES_NUMBER; ++i) {
		auto attribIG = entropy;
		for (auto split : count[i]) {
			auto setTotal = 0;
			for (auto clazz : split.second) {
				setTotal += clazz.second;
			}

			auto setEntropy = 0.0f;
			for (auto clazz : split.second) {
				auto p = clazz.second / (float)setTotal;
				setEntropy -= p * log(p) / log(2.0f);
			}
			attribIG -= (float)setTotal / (float)total * setEntropy;
		}
		if (attribIG >= ig.second) {
			ig.first = i;
			ig.second = attribIG;
		}
		}

		// Sort the set by the attribute index ig.first.
		auto attribIndex = ig.first;
		std::sort(start, end, [attribIndex](const Sample& a, const Sample& b) {
			return a.attributes[attribIndex] < b.attributes[attribIndex];
		});

		// Split the samples by the attributes.
		auto setStart = start;
		std::unordered_map<shortInt, std::unique_ptr<Node>> nodes;
		for (auto it = start; it != end; ++it) {
			if (it < end && it->attributes[attribIndex] == setStart->attributes[attribIndex]) {
				continue;
			}
			nodes[setStart->attributes[attribIndex]] = train(setStart, it);
			setStart = it;
		}

		return std::make_unique<InnerNode>(attribIndex, std::move(maxClazz), std::move(nodes));
	}

	std::vector<Sample> samples;
};