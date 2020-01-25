#pragma once
#include <string>
#include <limits.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <algorithm>

#define SET2

typedef __int16 shortInt;
typedef unsigned int uint;
typedef unsigned char uchar;


class HeartDiseaseData
{
public:
	const static uint NUMBER_OF_ATTR = 14;

	enum Cp { // chest pain type
		typicalAngina = 1,
		atypicalAngina = 2,
		nonAnginalPain = 3,
		asymptomatic = 4,
	};
	enum Restecg {
		normal = 0,
		STTWaveAbnormality = 1, // having ST-T wave abnormality (T wave inversions and/or ST elevation or depression of > 0.05 mV)
		leftVentricularHypertrophy = 2, // showing probable or definite left ventricular hypertrophy by Estes' criteria
	};
	enum Proto {
		Bruce = 1,
		Kottus = 2,
		McHenry = 3,
		fastBalke = 4,
		Balke = 5,
		Noughton = 6,
		bike_150_kpa = 7, // min/min (Not sure if "kpa min/min" is what was written!)
		bike_125_kpa = 8,	// min/min
		bike_100_kpa = 9,	// min/min
		bike_75_kpa = 10,	// min/min
		bike_50_kpa = 11,	// min/min
		armErgometer = 12,	// min/min
	};
	enum Slope {
		upsloping = 1,
		flat = 2,
		downsloping = 3,
	};
	enum Sp {
		none = 0,
		mildOrModerate = 1,
		moderateOrServe = 2,
		akinesisOrDyskmem = 3,
	};

private:
#ifdef SET1

	struct Set {

		/* 1 */ int ID;
		/* 2 */ int ccf; // dummy value 0
		/* 3 */ uint age;
		/* 4 */ bool sex; // (1 = male; 0 = female)
		/* 5 */ bool painloc; // (1 = substernal; 0 = otherwise)
		/* 6 */ bool painexer; // (1 = provoked by exertion; 0 = otherwise)
		/* 7*/ bool relrest; // (1 = relieved after rest; 0 = otherwise)
		/* 8 */ uint pncaden; // sum of 5, 6, 7
		/* 9 */ Cp cp; // chest pain type
		/* 10 */ uint trestbps; // resting blood pressure (in mm Hg on admission to the hospital)
		/* 11 */ int htn; // ?
		/* 12 */ uint chol; //serum cholestoral in mg / dl
		/* 13 */ bool smoke; // 1 = yes; 0 = no
		/* 14 */ uint cigs; //cigarettes per day
		/* 15 */ uint years; //number of years as a smoker
		/* 16 */ bool fbs; //(fasting blood sugar > 120 mg/dl) (1 = true; 0 = false)
		/* 17 */ bool dm; //(1 = history of diabetes; 0 = no such history)
		/* 18 */ bool famhist; //  family history of coronary artery disease (1 = yes; 0 = no)
		/* 19 */ Restecg restecg;
		/* 20 */ uint ekgmo; // month of exercise ECG reading
		/* 21 */ uint ekgday; // day of exercise ECG reading
		/* 22 */ uint ekgyr; // year of exercise ECG reading
		/* 23 */ bool dig; // digitalis used furing exercise ECG: 1 = yes; 0 = no
		/* 24 */ bool prop; // Beta blocker used during exercise ECG: 1 = yes; 0 = no
		/* 25 */ bool nitr; // nitrates used during exercise ECG: 1 = yes; 0 = no
		/* 26 */ bool pro; // calcium channel blocker used during exercise ECG: 1 = yes; 0 = no
		/* 27 */ bool diuretic; // diuretic used used during exercise ECG: 1 = yes; 0 = no
		/* 28 */ Proto proto; //exercise protocol
		/* 29 */ float thaldur; // duration of exercise test in minutes
		/* 30 */ int thaltime; // time when ST measure depression was noted
		/* 31 */ int met; // mets achieved
		/* 32 */ int thalach; // maximum heart rate achieved
		/* 33 */ int thalrest; // resting heart rate
		/* 34 */ uint tpeakbps;  //peak exercise blood pressure(first of 2 parts)
		/* 35 */ uint tpeakbpd; // peak exercise blood pressure (second of 2 parts)
		/* 36 */ int dummy;
		/* 37 */ uint trestbpd; //resting blood pressure
		/* 38 */ bool exang; // exercise induced angina (1 = yes; 0 = no)
		/* 39 */ bool xhypo; // (1 = yes; 0 = no)
		/* 40 */ int oldpeak; // ST depression induced by exercise relative to rest
		/* 41 */ Slope slope; // the slope of the peak exercise ST segment
		/* 42 */ uint rldv5; // height at rest
		/* 43 */ uint rldv5e; // height at peak exercise
		/* 44 */ uint ca; // number of major vessels (0-3) colored by flourosopy
		/* 45 */ int restckm; // irrelevant
		/* 46 */ int exerckm; // irrelevant

		// Mateusz - not sure about that below
		/* 47 */ Sp restef; // rest raidonuclid (sp?) ejection fraction
		/* 48 */ Sp restwm; // rest wall (sp?) motion abnormality
		/* 49 */ Sp exeref; // exercise radinalid (sp?) ejection fraction
		/* 50 */ Sp exerwm; // exercise wall (sp?) motion

		/* 51 */ uint thal; // 3 = normal; 6 = fixed defect; 7 = reversable defect
		/* 52 */ int thalsev; // not used
		/* 53 */ int thalpul; // not used
		/* 54 */ int earlobe; // not used
		/* 55 */ uint cmo; // month of cardiac cath (sp?) (perhaps "call")
		/* 56 */ uint cday; // day of cardiac cath (sp?)
		/* 57 */ uint cyr; // year of cardiac cath (sp?)
		/* 58 */ bool num; // Value 0: < 50% diameter narrowing; --Value 1: > 50 % diameter narrowing
	
		/* 59 */ int lmt; // vessel
		/* 60 */ int ladprox; // vessel
		/* 61 */ int laddist; // vessel
		/* 62 */ int diag; // vessel
		/* 63 */ int cxmain; // vessel
		/* 64 */ int ramus; // vessel
		/* 65 */ int om1; // vessel
		/* 66 */ int om2; // vessel
		/* 67 */ int rcaprox; // vessel
		/* 68 */ int rcadist; // vessel

		/* 69 */ int lvx1; // not used
		/* 70 */ int lvx2; // not used
		/* 71 */ int lvx3; // not used
		/* 72 */ int lvx4; // not used
		/* 73 */ int lvf; // not used
		/* 74 */ int cathef; // not used
		/* 75 */ int junk; // not used
		/* 76 */ std::string name; // last name of patient (I replaced this with the dummy string "name")
	};
#endif


	/*
	-------------------------------------------------------------------------------------------------------
	*/
#ifdef SET2

	// if the data says '?' there where is uchar then just set it to max.

	struct Set {

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

		/*
		Used types
		- uint
		- int
		- uchar
		- enum (unknow = 127)
		- float
		*/

		friend std::ostream& operator<<(std::ostream& stream, const Set& set);
	};

#endif

#ifdef SET3

	struct Set {
		/* 1 */ std::string age;
		/* 2 */ std::string sex; // (1 = male; 0 = female)
		/* 3 */ std::string cp;
		/* 4 */ std::string trestbps; // resting blood pressure (in mm Hg on admission to the hospital)
		/* 5 */ std::string chol; //serum cholestoral in mg / dl
		/* 6 */ std::string fbs; //(fasting blood sugar > 120 mg/dl) (1 = true; 0 = false)
		/* 7 */ std::string restecg;
		/* 8 */ std::string thalach; // maximum heart rate achieved
		/* 9 */ std::string exang; // exercise induced angina (1 = yes; 0 = no)
		/* 10 */ std::string oldpeak; // ST depression induced by exercise relative to rest
		/* 11 */ std::string slope; // the slope of the peak exercise ST segment
		/* 12 */ std::string ca; // number of major vessels (0-3) colored by flourosopy
		/* 13 */ std::string thal; // 3 = normal; 6 = fixed defect; 7 = reversable defect
		/* 14 */ std::string num; // Value 0: < 50% diameter narrowing; --Value 1: > 50 % diameter narrowing
	};

#endif
	friend std::ostream& operator<<(std::ostream& stream, const Set& set);

	std::vector<Set*>* dataSet;

	

	bool loadFile(const char* path, std::stringstream& stream);
	bool isDataSet = false;

public:
	HeartDiseaseData();
	~HeartDiseaseData();

	void readData(const char* path);
	void coutData();
};