// tempData.h 
//
// Johan Book
// 2017-10-28
//
// Reads temperature data into a class which contains said data
// Class contains suitable methods to read and manipulate data
//

#ifndef TEMPDATA_H
#define TEMPDATA_H

#include <string>
#include <vector>
#include "tempPoint.h"

class tempData
{

public:

	// Constructor with path to data file
	// Reads data and stores in this class
	tempData(std::string filePath);

	// Destructor
	~tempData() {}
	
	// Returns the temperature of a given date
	double getTemperature(int year, int month, int day); 

	// Calculates the mean temperature of a given year
	// ToDo: return standard deviation also
	double mean(int year); 
	
	// Calculates the mean temperature of a given month (for a given year)
	double mean(int year, int month); 

private:

	// Array to store data
	vector<tempPoint> data;
};

#endif
