// tempPoint.h
//
// Johan Book
// 2017-10-30
//
// Reads temperature data into a class which contains said data
// Class contains suitable methods to read and manipulate data
//

#ifndef TEMPPOINT_H
#define TEMPPOINT_H

#include <string>
#include <vector>


class tempPoint
{

public:

	// Reads date, time and temp. from string and stores it in this class
	tempPoint(std::string line);

	// Destructor
	~tempPoint() {}
	
	// Getters
	int getYear() {return year;}
	short int getMonth() {return month;}
	short int getDay() {return day;}
	short int getHour() {return hour;}
	double getTemperature() {return temp;}

private:

	// Data
	int year;
	short int month;
	short int day;
	short int hour;
	double temp;

	// Parses a string for some delimiter
	// Returns vector with substrings
	std::vector<std::string> parse_string(std::string line, char delimiter, int maxargs);
	
};

#endif
