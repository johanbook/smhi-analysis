// treader.h 
//
// Johan Book
// 2017-10-28
//
// Reads temperature data into a class which contains said data
// Class contains suitable methods to read and manipulate data
//

#ifndef TREADER_H
#define TREADER_H

#include <fstream>
#include <string>
#include <vector>
#include "tpoint.h"

class treader
{

public:

	// Constructor with path to data file
	// Reads data and stores in this class
	treader(std::string filePath);

	// Destructor
	~treader();

	// Returns whether there is more data to read
	bool has_next();	
	
	// Reads current line and converts it into a tpoint
	tpoint* get_tpoint();

private:
	
	// Input stream
	std::ifstream file;

	// Data format. True for Uppsala format and false for SMHI format
	tformat format;
};

#endif
