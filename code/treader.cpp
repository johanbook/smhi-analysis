// treader.cpp
//
// Johan Book
// 2017-10-28
//
// Reads temperature data, similar to ifstream.getline()
//

#include <cstdlib> // exit
#include <iostream> // cout
#include <fstream> // ifstream
#include <sstream> // istringstream
#include <string> // string
#include <vector> // vector
#include "treader.h"
#include "tpoint.h"
using namespace std;

// Constructor:  Open file 
treader::treader(string path) 
{
	file.open(path.c_str());
	if(!file.is_open())
	{
		cout << "ERROR: Unable to open " << path << "\n";
		exit(1);
	}
	
	// Check (from path) if Uppsala format
	uppsala = (path.find("Uppsala") != string::npos);
}

// Destructor
treader::~treader()
{
	file.close();
}

// Returns true if there is more data to read
bool treader::has_next()
{
	return file.peek() != EOF;
}

// Reads a line and converts it into a tpoint (ignores lines starting with #)
tpoint* treader::get_tpoint()
{
	// Read data until find non-commented line
	string line = "";
	while(getline(file,line))
		if(line[0] != '#' && line[3] != '#')
			return new tpoint(line, uppsala);
	
	// If it did not sucessfully return a point, exit program
	cout << "ERROR: Unable to read line\n";
	exit(1);
}


// TESTING: Main method to test class
int main(int argc, char* argv[])
{
	if(argc < 2)
	{
		cout << "Run program with path to file as argument\n";
		exit(1);
	}

	treader *tr = new treader(argv[1]);
	
	while(tr->has_next())
		tr->get_tpoint();
	delete tr;
	
	return 0;
}
