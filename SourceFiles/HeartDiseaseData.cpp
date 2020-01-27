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
	if (static_cast<double>(yes) + static_cast<double>(no) == 0.0) return 1.0f;
	return (1 - ((yes / (yes + no)) * (yes / (yes + no))) - ((no / (yes + no)) * (no / (yes + no))));
}

float HeartDiseaseData::countCutoff(int i)
{
	sort(dataSet->begin(), dataSet->end()-1,
		[&i](const Set* a, const Set* b) -> bool {
		return a->values[i] < b->values[i];
	});

	std::vector<float> averages, impurity;
	int yes = 0;
	int no = 0;
	for (auto it = dataSet->begin(); it != dataSet->end()-1; ++it)
	{
		if ((*it)->values[NUMBER_OF_ATTR - 1] == 0) ++no;
		else ++yes;

		float impurityLess = countImpurity((float)yes, (float)no);
		float impurityMore = countImpurity((float)(allYes - yes), (float)(allNo - no));
		impurity.push_back(((impurityLess * (float)(yes + no)) + (impurityMore*(float)(allYes + allNo - yes - no)))/ (float)(allYes + allNo));

		averages.push_back((((double)((*it)->values[i])) + ((double)((*(it+1))->values[i]))) / 2.0);
	}

	std::pair<float, int> minimpurity;
	minimpurity.first = 99;
	minimpurity.second = -1;
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
#ifdef SET1
	std::string* data = new std::string;
	data->reserve(100000);

	loadFile(path, *data);

	for (auto it : *data) {
		std::string tmp;
		int numb;
		float fnumb;
		bool isFloat = false;

		if (it >= 0x30 && it <= 0x39) {
			tmp = tmp + it;
		}
		else if (it == ',') {

		}
		else if (it == '.') {

		}
		else if (it == '?') {

		}
	}
#endif

#ifdef SET2

	

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

	cutoff[1] = cutoff[5] = cutoff[8] = 0;
	cutoff[0] = (shortInt)countCutoff(0);
	cutoff[2] = (shortInt)countCutoff(2);
	cutoff[3] = (shortInt)countCutoff(3);
	cutoff[4] = (shortInt)countCutoff(4);
	cutoff[6] = (shortInt)countCutoff(6);
	cutoff[7] = (shortInt)countCutoff(7);
	cutoff[9] = (shortInt)countCutoff(9);
	cutoff[10] = (shortInt)countCutoff(10);
	cutoff[11] = (shortInt)countCutoff(11);
	cutoff[12] = (shortInt)countCutoff(12);

#endif

#ifdef SET3
	std::stringstream stream;
	std::string* data = new std::string;
	data->reserve(100000);

	loadFile(path, stream);

	Set* set;
	dataSet->push_back(set = new Set());

	std::string tmp;
	uint index = 0;

	while (stream) {
		++index;
		stream >> tmp;

		switch (index) {
		case 3:
			set->age = tmp;
			break;
		case 4:
			set->sex = tmp;
			break;
		case 9:
			set->cp = tmp;
			break;
		case 10:
			set->trestbps = tmp;
			break;
		case 12:
			set->chol = tmp;
			break;
		case 16:
			set->fbs = tmp;
			break;
		case 19:
			set->restecg = tmp;
			break;
		case 32:
			set->thalach = tmp;
			break;
		case 38:
			set->exang = tmp;
			break;
		case 40:
			set->oldpeak = tmp;
			break;
		case 41:
			set->slope = tmp;
			break;
		case 44:
			set->ca = tmp;
			break;
		case 51:
			set->thal = tmp;
			break;
		case 58:
			set->num = tmp;
			break;
		case 76:
			index = 0;
			dataSet->push_back(set = new Set());
			break;
		}
	}

	delete data;

#endif

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
	for (int i = 0; i < NUMBER_OF_ATTR - 1; ++i) std::cout << cutoff[i] << " \t";
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
#ifdef SET2
	stream << set.values[0] << "\t" << set.values[1] << "\t" << set.values[2] << "\t" << set.values[3] << "\t" << set.values[4] << "\t" << set.values[5] << "\t" << set.values[6] << "\t" \
		<< set.values[7] << "\t" << set.values[8] << "\t" << set.values[9] << "\t" << set.values[10] << "\t" << set.values[11] << "\t" << set.values[12] << "\t" << set.values[13] << "\t";

	return stream;
#endif
}


#ifdef SET1
#undef SET1
#endif

#ifdef SET2
#undef SET2
#endif

#ifdef SET3
#undef SET3
#endif

#endif //HEARTDISEASEDATA_CPP
