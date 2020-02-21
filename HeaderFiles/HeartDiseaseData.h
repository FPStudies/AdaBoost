#ifndef HEARTDISEASEDATA_H
#define HEARTDISEASEDATA_H
#include <string>
#include <limits.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <algorithm>

#ifdef __linux__
typedef __int16_t shortInt;
#elif _WIN32
typedef __int16 shortInt;
#endif
typedef unsigned int uint;
typedef unsigned char uchar;


class HeartDiseaseData
{
public:
	const static uint NUMBER_OF_ATTR = 14;

private:

	// if the data says '?' there where is uchar then just set it to max.

	struct Set {

		// typical set of data

		/* 1 */// shortInt age;
		/* 2 */// shortInt sex; // (1 = male; 0 = female)
		/* 3 */// shortInt cp;
		/* 4 */// shortInt trestbps; // resting blood pressure (in mm Hg on admission to the hospital)
		/* 5 */// shortInt chol; //serum cholestoral in mg / dl
		/* 6 */// shortInt fbs; //(fasting blood sugar > 120 mg/dl) (1 = true; 0 = false)
		/* 7 */// shortInt restecg;
		/* 8 */// shortInt thalach; // maximum heart rate achieved
		/* 9 */// shortInt exang; // exercise induced angina (1 = yes; 0 = no)
		/* 10 */// shortInt oldpeak; // ST depression induced by exercise relative to rest
		/* 11 */// shortInt slope; // the slope of the peak exercise ST segment
		/* 12 */// shortInt ca; // number of major vessels (0-3) colored by flourosopy
		/* 13 */// shortInt thal; // 3 = normal; 6 = fixed defect; 7 = reversable defect
		/* 14 */// shortInt num; // Value 0: < 50% diameter narrowing; --Value 1: > 50 % diameter narrowing

		shortInt values[NUMBER_OF_ATTR];

		friend std::ostream& operator<<(std::ostream& stream, const Set& set);
	};

	friend std::ostream& operator<<(std::ostream& stream, const Set& set);

	bool loadFile(const char* path, std::stringstream& stream);
	float countCutoffLine(int i);

	bool isDataSet = false;

public:
	shortInt cutoffLine[NUMBER_OF_ATTR - 1];
	std::vector<Set*>* dataSet;
	int allYes, allNo;

	HeartDiseaseData();
	~HeartDiseaseData();

	static float countImpurity(float yes, float no);
	void readData(const char* path);
	void coutData();
	const bool isSet();
};

#endif //HEARTDISEASEDATA_H
