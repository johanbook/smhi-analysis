// tpoint.h
//
// Johan Book
// 2017-10-30
//
// Contains one point in time-temperature space and allows user to acces that data
// Also parses said data from string
//

#ifndef TPOINT_H
#define TPOINT_H

#include <string>
#include <vector>

enum tformat {SMHI, UPPSALA};

class tpoint
{

public:

	// Reads date, time and temp. from string and stores it in this class
	tpoint(std::string line, tformat format);

	// Destructor
	~tpoint() {}
	
	// Getters
	// If these return -1 there is no information
	int get_year() {return year;}
	short int get_month() {return month;}
	short int get_day() {return day;}
	short int get_hour() {return hour;}
	double get_temperature() {return temp;}

private:

	// Data
	int year = -1;
	short int month = -1;
	short int day = -1;
	short int hour = -1;
	double temp;

	// Parse data for SMHI and Uppsala (different formats
	void parse_smhi(std::string line);
	void parse_uppsala(std::string line);

	// Parses a string for some delimiter
	// Returns vector with substrings
	std::vector<std::string> parse_string(std::string line, char delimiter, int maxargs);
	
};

#endif
