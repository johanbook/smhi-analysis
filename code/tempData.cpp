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
		
		data.push_back(new tempPoint(line));
	}

	// Close file (obviously)
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
