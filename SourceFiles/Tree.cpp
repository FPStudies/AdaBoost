#include "../headerfiles/tree.h"

	shortInt ID3::classify(HeartDiseaseData::Set& sample)
	{
		return root->classify(sample);
	}

	void ID3::print(std::ostream& os)
	{
		root->print(os, 0);
	}

	TerminalNode :: TerminalNode(const shortInt clazz)
		: clazz(clazz) {}

		shortInt TerminalNode::classify(HeartDiseaseData::Set& sample) {
			return clazz;
		}

		void TerminalNode::print(std::ostream& os, size_t level) {
			for (size_t i = 0; i < level; ++i) {
				os << ' ';
			}
			os << clazz << std::endl;
		}

		shortInt InnerNode::classify(HeartDiseaseData::Set& sample) {
			auto it = branches.find(sample[attribute]);
			if (it == branches.end()) {
				return clazz;
			}
			else {
				return it->second->classify(sample);
			}
		}

		void InnerNode::print(std::ostream& os, size_t level) {
			auto tabs = [&os, level] {
				for (size_t i = 0; i < level; ++i) {
					os << ' ';
				}
			};
			for (const auto& branch : branches) {
				tabs(); os << branch.first << ":" << std::endl;
				branch.second->print(os, level + 1);
			}
		}


		// some shorthand aliases.
		using sample = typename HeartDiseaseData::Set;
		using iter = typename std::vector<sample&>::iterator;

	std::unique_ptr<ID3> ID3Train::train()
	{
		return std::unique_ptr<ID3>(new ID3(trainit(samples.begin(), samples.end())));
	}

	std::unique_ptr<Node> ID3Train::trainit(iter start, iter end)
	{
		auto ig = std::make_pair(0, std::numeric_limits<float>::min());
		std::unordered_map<shortInt, size_t> clazzes;
		shortInt maxclazz;

		// for each attribute/value pair, compute how many items fall into that category.
		std::array<std::unordered_map<shortInt, std::unordered_map<shortInt, size_t>>, HeartDiseaseData::NUMBER_OF_ATTR> count;
		for (auto it = start; it != end; ++it) {
			for (size_t i = 0; i < HeartDiseaseData::NUMBER_OF_ATTR; ++i) {
				count[i][it->values[i]][it->clazz]++;
			}
			clazzes[it->clazz]++;
		}

		// compute the entropy of the current set.
		auto entropy = 0.0f;
		auto total = end - start;
		for (auto clazz : clazzes) {
			auto p = clazz.second / (float)total;
			entropy -= p * log(p) / log(2.0f);

			if (clazz.second > clazzes[maxclazz]) {
				maxclazz = clazz.first;
			}
		}

		// if set is all classified, return leaf node.
		if (abs(entropy) <= EPS) {
			return std::make_unique<TerminalNode>(start->clazz);
		}

		// compute the information gain on all possible splits.
		for (size_t i = 0; i < HeartDiseaseData::NUMBER_OF_ATTR; ++i) {
			auto attribig = entropy;
			for (auto split : count[i]) {
				auto settotal = 0;
				for (auto clazz : split.second) {
					settotal += clazz.second;
				}

				auto setentropy = 0.0f;
				for (auto clazz : split.second) {
					auto p = clazz.second / (float)settotal;
					setentropy -= p * log(p) / log(2.0f);
				}
				attribig -= (float)settotal / (float)total * setentropy;
			}
			if (attribig >= ig.second) {
				ig.first = i;
				ig.second = attribig;
			}
		}

		// sort the set by the attribute index ig.first.
		auto attribindex = ig.first;
		std::sort(start, end, [attribindex](sample& a, sample& b) {
			return a.values[attribindex] < b.values[attribindex];
		});

		// split the samples by the attributes.
		auto setstart = start;
		std::unordered_map<shortInt, std::unique_ptr<Node>> nodes;
		for (auto it = start + 1; it != end + 1; ++it) {
			if (it < end && it->attributes[attribindex] == setstart->attributes[attribindex]) {
				continue;
			}
			nodes[setstart->attributes[attribindex]] = trainit(setstart, it);
			setstart = it;
		}

		return std::make_unique<InnerNode>(attribindex, std::move(maxclazz), std::move(nodes));
	}
