// tpoint.h
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


class tpoint
{

public:

	// Reads date, time and temp. from string and stores it in this class
	tpoint(std::string line);

	// Destructor
	~tpoint() {}
	
	// Getters
	int get_year() {return year;}
	short int get_month() {return month;}
	short int get_day() {return day;}
	short int get_hour() {return hour;}
	double get_temperature() {return temp;}

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
