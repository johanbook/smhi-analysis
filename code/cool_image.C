// cool_image.C
// 
// Johan Book
// 2017-11-01
//
// Plots an image
// Should be run from project root folder
//

// include C++ STL headers 
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "treader.h"
#include "tpoint.h"

using namespace std;

// ROOT library obejcts
#include <TF1.h> // 1d function class
#include <TGraphErrors.h> // TGraphErrors
#include <TH1.h> // 1d histogram classes
#include <TStyle.h>  // style object
#include <TMath.h>   // math functions
#include <TMultiGraph.h> // TMultiGraph
#include <TCanvas.h> // canvas object

// Read and analyze part
void generate_image();

// Creates a graph from a file specified in path, stored in results_i.png
TGraphErrors* createGraph(std::string path, int i);

// Standard deviation
double std_dev(vector<double> data, double mean);

///////////////////////////////////////////////////////////////
// Source Code
//////////////////////////////////////////////////////////////

// Reads data and generates several images
void generate_image() 
{
	// Path to all images
	string paths[] = {"data/Boras.csv", "data/Falsterbo.csv", "data/Falun.csv", "data/Karlstad.csv", "data/Lulea.csv", "data/Lund.csv", "data/Soderarm.csv", "data/Umea.csv", "data/Visby.csv"};	

	// Set ROOT drawing styles
	gStyle->SetOptStat(1111);
	gStyle->SetOptFit(1111);
	
	// Loop over all paths in paths[]
	for(int i = 0; i < 9; i++)
	{
		// TMultiGraph is here superfluous but hey, it works
		TMultiGraph* mg = new TMultiGraph();
		mg->Add(createGraph(paths[i],i));
	
		// Create canvas for hPhi
		TCanvas* c1 = new TCanvas("c1", "Temperature Bands", 900, 600);
		mg->Draw("a4");//Draw("a4");
	
		// Graph title, ranges, etc
		mg->GetYaxis()->SetLimits(-5,20);
		mg->GetYaxis()->SetTitle("Average Temperature");
		mg->GetXaxis()->SetLimits(1950,2020);
		mg->GetXaxis()->SetTitle("Year");
		
		// Save canvas as a picture
		stringstream ss;
		ss << "results/image" << (i+1) << ".png";
		cout << ss.str() << " was saved\n";
		c1->SaveAs(ss.str().c_str());
		delete c1;
	}
}

// Create a graph for one given path
TGraphErrors* createGraph(std::string path, int i)
{
	// Create treader (see treader.h) to parse temperature data in given path
	treader* tr = new treader(path);
	
	// Storage for necessary data
	vector<int> year;
	vector<double> temperature;
	vector<double> stddev;

	// Read from file while there is data to read
	int studied_year = -1;
	while(tr->has_next()){
		int data_year = studied_year;
		double tsum = 0; // temperature sum
		int nentries = 0; // number of entries
		vector<double> entries; // entries for this year
		
		// While the 
		while(tr->has_next() && studied_year == data_year)
		{
			nentries++;
			tpoint* tp = tr->get_tpoint();
			tsum += tp->get_temperature();
			entries.push_back(tp->get_temperature());
	
			data_year = tp->get_year();	
			
			// If studied year has not been intialized, then initialize it
			if(studied_year == -1)
				studied_year = data_year;
		}
		
		// Store year, temperature and standard deviation
		year.push_back(studied_year);
		temperature.push_back(tsum/nentries);
		stddev.push_back(std_dev(entries, tsum/nentries));

		studied_year = data_year;
	}

	// Data to create actual graph
	int n = year.size();
	double x[n];
	double xe[n];
	double y[n];
	double ye[n];
	
	// Extract data from vectors
	for(int k = 0; k < n; k++)
	{
		x[k] = year[k];
		xe[k] = 0;
		y[k] = temperature[k];
		ye[k] = stddev[k];
	}

	// Create graphs
	TGraphErrors* graph = new TGraphErrors(n,x,y,xe,ye);
	
	// Set fill colors (color 1,2, 10 are undesired and skipped)
	if(3+i != 10)
		graph->SetFillColor(3+i);
	else
		graph->SetFillColor(25);//some random color
	
	return graph;
}

// Standard deviation
double std_dev(vector<double> data, double avg)
{
	double sum = 0;
	for(size_t i = 0; i < data.size(); i++)
		sum += (data[i] - avg)*(data[i] - avg);
	return TMath::Sqrt(sum/(data.size()-1));
}
