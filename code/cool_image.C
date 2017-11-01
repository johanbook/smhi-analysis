// cool_image.C
// 
// Johan Book
// 2017-11-01
//
// Plots an image
//

// include C++ STL headers 
#include <iostream>
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
TGraphErrors* createGraph(std::string path);

// Standard deviation
double std_dev(vector<double> data, double mean);

///////////////////////////////////////////////////////////////
// Source Code
//////////////////////////////////////////////////////////////

// Reads data and generates
void generate_image(std::string path) 
{
	string paths[] = {"data/Boras.csv", "data/Falsterbo.csv", "data/Lulea.csv", "data/Lund.csv"};	

	TMultiGraph* mg = new TMultiGraph();
	for(int i = 0; i < 1; i++)
		mg->Add(createGraph(paths[i]));
	
	// Set ROOT drawing styles
	gStyle->SetOptStat(1111);
	gStyle->SetOptFit(1111);

	// Create canvas for hPhi
	TCanvas* c1 = new TCanvas("c1", "canvas", 900, 600);
	//mg->SetMinimum(0);
	//mg->SetFillColorAlpha(kBlue, 0.1);
	mg->Draw("a4");

	// Save canvas as a picture
	c1->SaveAs("cool_image.png");
}

TGraphErrors* createGraph(std::string path)
{
	treader* tr = new treader(path);

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
	int n = year.size();
	double x[n];
	double xe[n];
	double y[n];
	double ye[n];
	for(int i = 0; i < n; i++)
	{
		x[i] = year[i];
		xe[i] = 0;
		y[i] = temperature[i];
		ye[i] = stddev[i];
	}
	TGraphErrors* graph = new TGraphErrors(n,x,y,xe,ye);
	graph->SetFillColor(6);
	graph->SetFillStyle(3005);
	//graph->SetFillColorAlpha(kBlue, 0.1);
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
