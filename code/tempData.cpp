#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "tempData.h"
using namespace std;

// Constructor
tempData::tempData(string path) 
{
	// Open file reader
	ifstream file(path);
	if(!file.is_open())
	{
		cout << "ERROR: Unable to open " << path << "\n";
		exit(1);
	}

	// Read data
	string line;
	while(getline(file,line))
	{
		// Skip lines starting with #
		if(line[0] == '#')
			continue;
		
		cout << line << " == "; // For testing
		
		// Parse line
		vector<string> parsed = (line, ";", 9);	
		for(int i = 0; i < parsed.size(); i++)
		{
			cout << parsed.at(i); // For testing
		}
		cout << "\n";
	}

	file.close();
}

// Parses a string for some delimiter and returns vector with substrings
vector<string> parse_string(string line, char delimiter, int maxargs)
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

// Main method to test class
int main(int argc, char* argv[])
{
	if(argc < 2)
	{
		cout << "Run program with path to file as argument\n";
		exit(1);
	}

	tempData *data = new tempData(argv[1]);

	return 0;
}
