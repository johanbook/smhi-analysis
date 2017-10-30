#include <cstdlib> // exit
#include <iostream> // cout
#include <fstream> // ifstream
#include <sstream> // istringstream
#include <string> // string
#include <vector> // vector
#include "tempData.h"
using namespace std;

// FOR TESTING
void print_vector(vector<string> vec)
{
	for(int i = 0; i < vec.size(); i++)
		cout << vec.at(i) << " ";
}

// Constructor
tempData::tempData(string path) 
{
	// Open file reader
	ifstream file(path.c_str());
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
		
		cout << line << "\t> "; // For testing
		
		// Parse line, assuming 3 arguments (data, time, temp)
		vector<string> parsed = parse_string(line, ';', 3);
	
		// Parse date
		vector<string> date = parse_string(parsed.at(0), '-', 3);

		// Parse time	
		vector<string> time = parse_string(parsed.at(1), ':', 3);

		// TESTING
		print_vector(date);
		cout << ":: ";
		print_vector(time);
		cout << ":: " << parsed.at(2) << "\n";
	}

	// Close file (obviously)
	file.close();
}

// Parses a string for some delimiter and returns vector with substrings
vector<string> tempData::parse_string(string line, char delimiter, int maxargs)
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
