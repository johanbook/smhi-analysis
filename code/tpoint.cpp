// tpoint.cpp
//
// Johan Book
// 2017-10-30
//

#include <iostream> // cout
#include <sstream> // istringstream
#include <stdlib.h> // atoi, atof
#include <string> // string
#include <vector> // vector
#include "tpoint.h"
using namespace std;

// Constructor
// Takes string with data and parses it (not for Uppsala)
tpoint::tpoint(string line, tformat format) 
{
	if(format == UPPSALA)
		parse_uppsala(line);
	else
		parse_smhi(line);

	// Debug
	//cout << line << "\n";
	if(format == UPPSALA)
		cout << year << "-" << month << "-" << day << " " << temp << "\n";
	else
		cout << year << "-" << month << "-" << day << " " 
		<< hour << " " << temp << "\n";
}

// Parses SMHI data
void tpoint::parse_smhi(string line)
{
	// Parse line, assuming 3 arguments (data, time, temp)
	vector<string> parsed = parse_string(line, ';', 3);
	vector<string> date = parse_string(parsed.at(0), '-', 3);
	vector<string> time = parse_string(parsed.at(1), ':', 3);

	// Store it
	year = atoi(date.at(0).c_str());
	month = atoi(date.at(1).c_str());
	day = atoi(date.at(2).c_str());
	hour = atoi(time.at(0).c_str());
	temp = atof(parsed.at(2).c_str());
}

// Parses Uppsala data
void tpoint::parse_uppsala(string line)
{
	istringstream string_reader(line);
    	string_reader >> year >> month >> day >> temp;
}

// Parses a string for some delimiter and returns vector with substrings
vector<string> tpoint::parse_string(string line, char delimiter, int maxargs)
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
