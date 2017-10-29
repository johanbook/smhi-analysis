#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "tempData.h"
using namespace std;

// Constructor
tempData::tempData(string path) 
{
	cout << "Path: " << path << "\n";
	
	// Open file reader
	ifstream file(path);
	if(!file.is_open())
	{
		cout << "ERROR: Unable to open " << path << "\n";
		exit(1);
	}

	// Read data
	// set delimiter ?;
	string line;
	while(getline(file,line))
	{
		// Skip lines starting with #
		if(line[0] == '#')
			continue;
		
		cout << line << " == ";
		
		// Parse line
		istringstream string_reader(line);	
		string date = "";
		double temperature = 0;
		for(;string_reader;)
		{	
			string s;
			if(!getline(string_reader, s, ';'))
				break;
			cout << s << " ";
		}
		cout << "\n";
	}

	file.close();
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
