// tempPoint.cpp
//
// Johan Book
// 2017-10-30
//

#include <sstream> // istringstream
#include <string> // string
#include <vector> // vector
#include "tempPoint.h"
using namespace std;

// Constructor
tempPoint::tempPoint(string line) 
{
	// Parse line, assuming 3 arguments (data, time, temp)
	vector<string> parsed = parse_string(line, ';', 3);
	
	// Parse date
	vector<string> date = parse_string(parsed.at(0), '-', 3);

	// Parse time	
	vector<string> time = parse_string(parsed.at(1), ':', 3);

	// Store it
	year = static_cast<int>(date.at(0));
	month = static_cast<short int>(date.at(1));
	day = static_cast<short int>(date.at(2));
	hour = static_cast<short int>(time.at(0));
	temp = static_cast<double>(parsed.at(2));
}

// Parses a string for some delimiter and returns vector with substrings
vector<string> tempPoint::parse_string(string line, char delimiter, int maxargs)
{
	istringstream string_reader(line);	
	vector<string> parsed;
	for(int i = 0; i < maxargs && string_reader; i++)
	{	
		string substring;
		if(!getline(string_reader, substring, delimiter))
			break;
		parsed.push_back(substring);
	}
	return parsed;
}
