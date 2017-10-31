// tempPoint.cpp
//
// Johan Book
// 2017-10-30
//

#include <iostream>
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
	year = atoi(date.at(0).c_str());
	month = stoi(date.at(1).c_str());
	day = stoi(date.at(2).c_str());
	hour = stoi(time.at(0).c_str());
	temp = stoi(parsed.at(2).c_str());

	// Debug
	cout << year << month << day << hour << temp << endl;
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
