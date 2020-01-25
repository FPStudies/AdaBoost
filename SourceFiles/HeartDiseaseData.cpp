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



void HeartDiseaseData::readData(const char * path)
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

	std::stringstream stream;

	Set* set;
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
		
			file >> set->age;

			file >> set->sex;
			file >> set->cp;
			file >> set->trestbps;
			file >> set->chol;
			file >> set->fbs;
			file >> set->restecg;
			file >> set->thalach;
			file >> set->exang;

			file >> ftmp;
			set->oldpeak = static_cast<int>(ftmp * 10);

			file >> set->slope;
			file >> set->ca;
			file >> set->thal;
			file >> set->num;

			dataSet->push_back(set = new Set());
		}

		file.close();
	}
	catch (std::exception & e) {
		std::cout << e.what() << std::endl;
		return;
	}

	


#endif

#ifdef SET3
	std::stringstream stream;
	std::string *data = new std::string;
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
	stream << set.age << "\t" << set.sex << "\t" << set.cp << "\t" << set.trestbps << "\t" << set.chol << "\t" << set.fbs << "\t" << set.restecg << "\t" \
		<< set.thalach << "\t" << set.exang << "\t" << set.oldpeak << "\t" << set.slope << "\t" << set.ca << "\t" << set.thal << "\t" << set.num << "\t";

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