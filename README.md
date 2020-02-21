# AdaBoost
**AdaBoost with decision tree sequence.**

###### How to use
Input have 2 files. The first one is for teaching, the second one is for validating. The first number indicates how many records there is in file. Record is divided as follow:
1. age
2. sex 			// (1 = male; 0 = female)
3. cp			// chest pain type (4 types 1-4)
4. trestbps 	// resting blood pressure (in mm Hg on admission to the hospital)
5. chol			// serum cholestoral in mg / dl
6. fbs			// (fasting blood sugar > 120 mg/dl) (1 = true; 0 = false)
7. restecg		// resting electrocardiographic results (3 types 0-2)
8. thalach		// maximum heart rate achieved
9. exang		// exercise induced angina (1 = yes; 0 = no)
10. oldpeak		// ST depression induced by exercise relative to rest
11. slope		// the slope of the peak exercise ST segment
12. ca			// number of major vessels (0-3) colored by flourosopy
13. thal		// 3 = normal; 6 = fixed defect; 7 = reversable defect
14. num			// Value 0: < 50% diameter narrowing; --Value 1: > 50 % diameter narrowing

Data was fetch from https://archive.ics.uci.edu/ml/datasets/Heart+Disease where you can find more information.
Caution - data present on the above page has been processed to match the program input. 

###### Details
Program was write based on https://youtu.be/LsK-xG1cLYA on youtube where everything is clearly explained.

Program was written in C++ based on compiler version 14 or higher.