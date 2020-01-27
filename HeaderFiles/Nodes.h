#ifndef NODE_H
#define NODE_H
#include <unordered_map>
#include "HeartDiseaseData.h"
#include "Sample.h"

class Node {
public:
	Node(size_t attribute, shortInt cutoff): attribute(attribute), cutoff(cutoff) {}

	shortInt classify(const std::array<shortInt, Sample::ATTRIBUTES_NUMBER>& sample) {
		if (sample[attribute] <= cutoff) return 0;
		else return 1;
	}

private:
	size_t attribute;
	shortInt cutoff;
};

#endif //NODE_H
