#include "../HeaderFiles/HeartDiseaseData.h"

HeartDiseaseData::HeartDiseaseData()
{
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
	dataSet->push_back(new Set());	// first Set is for median
	dataSet->push_back(set = new Set());

	std::ifstream file;
	file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try {
		file.open(path);
		uint iter;
		file >> iter;

		for (uint i = 0; i < iter; ++i) {
			float ftmp;
			std::string tmp;

			for (uint j = 0; j < NUMBER_OF_ATTR; ++j) {
				if (j != 9) file >> set->values[j];
				else {
					file >> ftmp;
					set->values[j] = static_cast<int>(ftmp * 10);
				}
			}

			dataSet->push_back(set = new Set());
		}

		file.close();
	}
	catch (std::exception & e) {
		std::cout << e.what() << std::endl;
		return;
	}
	Set* first = (*dataSet)[0];

	for (uint i = 0; i < NUMBER_OF_ATTR; ++i) {
		first->values[i] = 0;
	}

	sort(dataSet->begin() + 1, dataSet->end(),
		[](const Set* a, const Set* b) -> bool {
		return a->values[0] > b->values[0];
	});
	first->values[0] = dataSet->size() % 2 == 0 ? ((*dataSet)[dataSet->size() / 2]->values[0] + (*dataSet)[dataSet->size() / 2 + 1]->values[0]) / 2 : (*dataSet)[(dataSet->size() + 1) / 2]->values[0];

	sort(dataSet->begin() + 1, dataSet->end(),
		[](const Set* a, const Set* b) -> bool {
		return a->values[3] > b->values[3];
	});
	first->values[3] = dataSet->size() % 2 == 0 ? ((*dataSet)[dataSet->size() / 2]->values[3] + (*dataSet)[dataSet->size() / 2 + 1]->values[3]) / 2 : (*dataSet)[(dataSet->size() + 1) / 2]->values[3];

	sort(dataSet->begin() + 1, dataSet->end(),
		[](const Set* a, const Set* b) -> bool {
		return a->values[4] > b->values[4];
	});
	first->values[4] = dataSet->size() % 2 == 0 ? ((*dataSet)[dataSet->size() / 2]->values[4] + (*dataSet)[dataSet->size() / 2 + 1]->values[4]) / 2 : (*dataSet)[(dataSet->size() + 1) / 2]->values[4];

	sort(dataSet->begin() + 1, dataSet->end(),
		[](const Set* a, const Set* b) -> bool {
		return a->values[7] > b->values[7];
	});
	first->values[7] = dataSet->size() % 2 == 0 ? ((*dataSet)[dataSet->size() / 2]->values[7] + (*dataSet)[dataSet->size() / 2 + 1]->values[7]) / 2 : (*dataSet)[(dataSet->size() + 1) / 2]->values[7];

	sort(dataSet->begin() + 1, dataSet->end(),
		[](const Set* a, const Set* b) -> bool {
		return a->values[9] > b->values[9];
	});
	first->values[9] = dataSet->size() % 2 == 0 ? ((*dataSet)[dataSet->size() / 2]->values[9] + (*dataSet)[dataSet->size() / 2 + 1]->values[9]) / 2 : (*dataSet)[(dataSet->size() + 1) / 2]->values[9];


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
	std::cout.flush();
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