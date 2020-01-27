#pragma once
#include <unordered_map>
#include "HeartDiseaseData.h"
#include "Sample.h"

//class Node {
//public:
//	virtual ~Node() {};
//	virtual shortInt classify(const std::array<shortInt, Sample::ATTRIBUTES_NUMBER>& sample) = 0;
//	virtual void print(std::ostream& os, size_t level) = 0;
//};

//class TerminalNode : public Node {
//public:
//	TerminalNode(const shortInt& clazz) : clazz(clazz) {};
//
//	shortInt classify(const std::array<shortInt, Sample::ATTRIBUTES_NUMBER>& sample) override {
//		return clazz;
//	}
//
//	void print(std::ostream& os, size_t level) override {
//		for (size_t i = 0; i < level; ++i) {
//			os << ' ';
//		}
//		os << clazz << std::endl;
//	}
//
//private:
//	shortInt clazz;
//};

/// Inner node that makes a decision.
class /*InnerNode : public*/ Node {
public:
	/*Inner*/Node(size_t attribute, shortInt cutoff): attribute(attribute), cutoff(cutoff) {}

	shortInt classify(const std::array<shortInt, Sample::ATTRIBUTES_NUMBER>& sample) /*override*/ {
		if (sample[attribute] <= cutoff) return 0;
		else return 1;
	}

	/*void print(std::ostream& os, size_t level) override {
		auto tabs = [&os, level] {
			for (size_t i = 0; i < level; ++i) {
				os << ' ';
			}
		};
		for (const auto& branch : branches) {
			tabs(); os << branch.first << ":" << std::endl;
			branch.second->print(os, level + 1);
		}
	}*/

private:
	size_t attribute;
	shortInt cutoff;
	
};