#ifndef HEARTDISEASEDATA_CPP
#define HEARTDISEASEDATA_CPP

#include "../HeaderFiles/HeartDiseaseData.h"

HeartDiseaseData::HeartDiseaseData()
{
	allYes = allNo = 0;
	dataSet = new std::vector<Set*>();
	dataSet->reserve(1400);
}

HeartDiseaseData::~HeartDiseaseData()
{
	for (auto it : *dataSet) {
		delete it;
	}
	delete dataSet;
}

bool HeartDiseaseData::loadFile(const char* path, std::stringstream& stream)
{
	std::ifstream file;
	file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try {
		file.open(path);
		std::stringstream stream;
		stream << file.rdbuf();
		file.close();
	}
	catch (std::exception & e) {
		std::cout << e.what() << std::endl;
		return true;
	}
	return false;
}

float HeartDiseaseData::countImpurity(float yes, float no)
{
	float tmp = yes + no;
	if (tmp == 0.0f) return 1.0f;
	return (1 - ((yes / (tmp)) * (yes / (tmp))) - ((no / (tmp)) * (no / (tmp))));
}

float HeartDiseaseData::countCutoffLine(int i)
{
	// sort by i-th value
	sort(dataSet->begin(), dataSet->end()-1,
		[&i](const Set* a, const Set* b) -> bool {
		return a->values[i] < b->values[i];
	});

	// the average value of the attribute and impurity of the choice
	std::vector<float> averages, impurity;

	// for counting if the disease is present or not
	int yes = 0;
	int no = 0;

	for (auto it = dataSet->begin(); it != dataSet->end() - 1; ++it)
	{
		if ((*it)->values[NUMBER_OF_ATTR - 1] == 0) ++no;	// the last atribute tell us about disease
		else ++yes;

		float impurityLess = countImpurity((float)yes, (float)no);
		float impurityMoreOrEqual = countImpurity((float)(allYes - yes), (float)(allNo - no));
		impurity.push_back(((impurityLess * (float)(yes + no)) + (impurityMoreOrEqual * (float)(allYes + allNo - yes - no)))/ (float)(allYes + allNo));

		averages.push_back(((*it)->values[i] + ((*(it + 1))->values[i])) / 2.0f);
	}

	// find the lowest impurity
	std::pair<float, int> minimpurity;
	minimpurity.first = 99; // for impurity value
	minimpurity.second = -1; // for average attribute value
	for (int j = 0; j < impurity.size(); ++j)
	{
		if (impurity[j] <= minimpurity.first)
		{
			minimpurity.first = impurity[j];
			minimpurity.second = j;
		}
	}

	return averages[minimpurity.second];
}

void HeartDiseaseData::readData(const char* path)
{
	Set* set;

	std::ifstream file;
	file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try {
		file.open(path);
		uint iter;
		file >> iter;

		for (uint i = 0; i < iter; ++i) {
			dataSet->push_back(set = new Set());

			for (uint j = 0; j < NUMBER_OF_ATTR; ++j) {
				file >> set->values[j];
			}
			if (set->values[NUMBER_OF_ATTR - 1] == 0) ++allNo;
			else ++allYes;			
		}

		file.close();
	}
	catch (std::exception & e) {
		std::cout << e.what() << std::endl;
		return;
	}

	// because of boolean values
	cutoffLine[1] = cutoffLine[5] = cutoffLine[8] = 0;	

	// the rest of values types
	cutoffLine[0] = (shortInt)countCutoffLine(0);
	cutoffLine[2] = (shortInt)countCutoffLine(2);
	cutoffLine[3] = (shortInt)countCutoffLine(3);
	cutoffLine[4] = (shortInt)countCutoffLine(4);
	cutoffLine[6] = (shortInt)countCutoffLine(6);
	cutoffLine[7] = (shortInt)countCutoffLine(7);
	cutoffLine[9] = (shortInt)countCutoffLine(9);
	cutoffLine[10] = (shortInt)countCutoffLine(10);
	cutoffLine[11] = (shortInt)countCutoffLine(11);
	cutoffLine[12] = (shortInt)countCutoffLine(12);

	isDataSet = true;
}

void HeartDiseaseData::coutData()
{
	if (!isDataSet) {
		std::cout << "Buffer empty" << std::endl;
		return;
	}

	for (auto it : *dataSet) {
		std::cout << *it << "\n";
	}

	std::cout << "\nCutoff points:\n";
	for (int i = 0; i < NUMBER_OF_ATTR - 1; ++i) std::cout << cutoffLine[i] << " \t";
	std::cout << "\n";
	std::cout << dataSet->size();
	std::cout.flush();
}

const bool HeartDiseaseData::isSet()
{
	return isDataSet;
}

std::ostream& operator<<(std::ostream& stream, const HeartDiseaseData::Set& set)
{
	stream << set.values[0] << "\t" << set.values[1] << "\t" << set.values[2] << "\t" << set.values[3] << "\t" << set.values[4] << "\t" << set.values[5] << "\t" << set.values[6] << "\t" \
		<< set.values[7] << "\t" << set.values[8] << "\t" << set.values[9] << "\t" << set.values[10] << "\t" << set.values[11] << "\t" << set.values[12] << "\t" << set.values[13] << "\t";

	return stream;
}

#endif //HEARTDISEASEDATA_CPP
