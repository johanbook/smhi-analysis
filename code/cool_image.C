// cool_image.C
// 
// Johan Book
// 2017-11-01
//
// Plots an image
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
void generate_image(std::string path);

// Creates a graph
TGraphErrors* createGraph(std::string path, int i);

// Standard deviation
double std_dev(vector<double> data, double mean);

///////////////////////////////////////////////////////////////
// Source Code
//////////////////////////////////////////////////////////////

// Reads data and generates
void generate_image(std::string path) 
{
	string paths[] = {"data/Boras.csv", "data/Falsterbo.csv", "data/Falun.csv", "data/Karlstad.csv", "data/Lulea.csv", "data/Lund.csv", "data/Soderarm.csv", "data/Umea.csv", "data/Visby.csv"};	

	// Set ROOT drawing styles
	gStyle->SetOptStat(1111);
	gStyle->SetOptFit(1111);


	// Multigraph containing all graphs
	//TMultiGraph* mg = new TMultiGraph();
	
	
	for(int i = 0; i < 9; i++)
	{
		TMultiGraph* mg = new TMultiGraph(); // REMOVE THIS LINE
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
		cout << "======================Path: " << ss.str() << "\n";
		c1->SaveAs(ss.str().c_str());
		delete c1;
	}
}

// Create a graph for one given path
TGraphErrors* createGraph(std::string path, int i)
{
	treader* tr = new treader(path);
	
	// Storage for necessary data
	vector<int> year;
	vector<double> temperature;
	vector<double> stddev;

	// Read from file while there is data to read
	int year1 = -1;
	while(tr->has_next()){
		int year2 = year1;
		double tsum = 0;
		int nentries = 0;
		vector<double> entries;
		while(tr->has_next() && year1 == year2)
		{
			tpoint* tp = tr->get_tpoint();
			tsum += tp->get_temperature();
			entries.push_back(tp->get_temperature());
			nentries++;
			year2 = tp->get_year();	
			if(year1 == -1)
				year1 = year2;
		}
		year.push_back(year1);
		temperature.push_back(tsum/nentries);
		stddev.push_back(std_dev(entries, tsum/nentries));

		year1 = year2;
		
		cout << year1 << " " << tsum / nentries << "\n";
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
	if(3+i != 10)
		graph->SetFillColor(3+i);
	else
		graph->SetFillColor(25);
	//graph->SetFillStyle(0); //4050 should be semi-transparent
	//graph->SetFillColorAlpha(9, 0.571);
	//graph->SetLineColorAlpha(i,1);
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
