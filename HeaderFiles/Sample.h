#ifndef SAMPLE_H
#define SAMPLE_H
#include <iostream>
#include "HeartDiseaseData.h"
#include <array>
#include <math.h>


struct Sample {
	const static uint ATTRIBUTES_NUMBER = HeartDiseaseData::NUMBER_OF_ATTR - 1;

	// Array of attributes of the sample.
	std::array<shortInt, ATTRIBUTES_NUMBER> attributes;
	// Class to which the sample belongs.
	shortInt clazz;
	// Sample weight
	long double weight;


	Sample()  noexcept : attributes(std::array<shortInt, ATTRIBUTES_NUMBER>()), clazz(0), weight(0) {};

	Sample(const Sample& other) : attributes(other.attributes), clazz(other.clazz), weight(other.weight) {};

	Sample(Sample&& sample)  noexcept : attributes(std::move(sample.attributes)), clazz(std::move(sample.clazz)), weight(std::move(sample.weight)) {}

	void operator = (const Sample& sample) noexcept {
		attributes = sample.attributes;
		clazz = sample.clazz;
		weight = sample.weight;
	}

	void swap(Sample& a, Sample& b)
	{
		Sample tmp = a;
		a = b;
		b = tmp;
	}

	long double newWeight(double treeWeight)
	{
		weight = weight * exp(treeWeight);
		return weight;
	}

	friend std::ostream& operator<<(std::ostream& stream, const Sample& sample)
	{

		for (int i = 0; i < ATTRIBUTES_NUMBER; ++i) stream << sample.attributes[i] << " \t";
		stream << sample.clazz << " \t";

	return stream;
	}
};

#endif //SAMPLE_H

