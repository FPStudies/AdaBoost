#pragma once
#include <iostream>
#include "HeartDiseaseData.h"
#include <array>


struct Sample {
	const static uint ATTRIBUTES_NUMBER = HeartDiseaseData::NUMBER_OF_ATTR - 1;

	// Array of attributes of the sample.
	std::array<shortInt, ATTRIBUTES_NUMBER> attributes;
	// Class to which the sample belongs.
	shortInt clazz;
	long double weight;


	Sample()  noexcept : attributes(std::array<shortInt, ATTRIBUTES_NUMBER>()), clazz(0) {};

	Sample(Sample&& sample)  noexcept : attributes(std::move(sample.attributes)), clazz(std::move(sample.clazz)) {}

	void operator = (Sample&& sample) noexcept {
		attributes = std::move(sample.attributes);
		clazz = std::move(sample.clazz);
	}
};