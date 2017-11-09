// global_warming.C
// 
// Edvin Jakobsson
// MNXB01 project 
// 2017-11-06
//
// 
// Reads data from file, from given start year to end year, and draws a histogram of the average temperature for different years
// Two graphs are also added to the histogram displaying moving averages (average temperature over a couple of years)
// The code works with any of the given data files, but the limited amount of data in all but the "Uppsala.dat" makes this kind of histogram rather unrewarding for those data files
// Make sure that the given start year is not prior to the available data in the data file

// include C++ STL headers that are used to read the data
#include <iostream>
#include <fstream>
#include "treader.h"
#include "tpoint.h"

using namespace std;

// ROOT library objects
#include <TF1.h> 		// 1d function class
#include <TH1.h> 		// 1d histogram classes
#include <TStyle.h> 	// style object
#include <TMath.h>   	// math functions
#include <TCanvas.h> 	// canvas object
#include <TGaxis.h>		// axis object needed to change the y-axis
#include <TLegend.h>	// Legend object
#include <TGraph.h>		// graph object



// Reads data and generates a histogram of the average temperature over different years
void global_warming_function(string path, int startYear, int endYear) {		// argument is path of data file (e.x. "../data/Uppsala.dat")
			
	// create an object that can read the data (see "treader.h")		
	treader* tr = new treader(path);
	
	int numberOfYears = (endYear-startYear+1);	// +1 because the end year is included
	double averageTemp[numberOfYears];			// array saving all values for the average temperature of each year
	int numberOfDatapointsPerYear = 0;			// counter for the number of values from each year (some years have 366 days, some has multiple measurements every day...)

	// clears any previous data in the array
	for(int i = 0; i < numberOfYears; ++i)
		averageTemp[i] = 0;
	
	// fills the array with average temperature from each year
	for(int i = 0; i < numberOfYears; ++i){

		// Reads from file until the end of a year is reached
		while(tr->has_next()){
	
			// Get tpoint, an object that saves the year and temperature for a data point (see "tpoint.h")
			tpoint* tp = tr->get_tpoint();
	
			// breaks while-loop if a new year is reached
			if(tp->get_year() > i + startYear){
				averageTemp[i+1] = tp->get_temperature();	//saves this value in the next slot in the array, so that we dont lose it
				break;
			}

			// adds the temperature of the current data point only if the data point is from the correct year (this makes the code skip all data points from years prior to the requested start year)
			if(tp->get_year() == i + startYear){
				++numberOfDatapointsPerYear;
				averageTemp[i] += tp->get_temperature();
			}
		}
		
		averageTemp[i] /= numberOfDatapointsPerYear;
		numberOfDatapointsPerYear = 1;		// 1 because of the value added just before the break
	}
	
	//calculates a total average over all years
	double totAverage = 0;
	for(int i = 0; i < numberOfYears; ++i){
		totAverage += averageTemp[i]/numberOfYears;
	}

	// Creates canvas
	TCanvas* c1 = new TCanvas("c1", "Average Temperature", 900, 600);
	
	// Creates histograms
	TH1F* histoRed = new TH1F("Red", ";Year; Temperature [#circ C]",numberOfYears , startYear, endYear);	
	TH1F* histoBlue = new TH1F("Blue", "; Year; Temperature [#circ C",numberOfYears , startYear, endYear);
	
	// adds the temperatures to the histograms
	for(int i = 0; i<numberOfYears; ++i){
		double temp = averageTemp[i] - totAverage;	//temperatures being focused around 0 instead of the total average. I was only able to create the picture with the blue pillars dropping down from zero, so I eventually solved it by creating a new "fake" y-axis instead
		averageTemp[i] -= totAverage;
		if(temp >= 0)
			histoRed->SetBinContent(i+1,temp);
		else
			histoBlue->SetBinContent(i+1,temp);	
		}	
		
	//Creates a legend
	TLegend *legend = new TLegend(0.65, 0.80, 0.94, 0.94, "", "NDC");
	legend->SetFillStyle(0); 
	legend->SetBorderSize(0);
	legend->AddEntry(histoRed, "Above average temperature", "F"); 
	legend->AddEntry(histoBlue, "Below average temperature", "F");
	
	// Creates a graph showing a moving average
	int movingAverageRange = 10;
	int movingAverageSteplength = 10;
	TGraph* graph1 = new TGraph();
	for(int bin = movingAverageRange; bin < numberOfYears-movingAverageRange; bin += movingAverageSteplength) {
		double movingAverage = 0;	
		for(int i = -movingAverageRange; i <= movingAverageRange; ++i){ 
			movingAverage += (averageTemp[bin+i]/(movingAverageRange*2+1));
		}	
		graph1->SetPoint(graph1->GetN(), histoRed->GetBinCenter(bin),movingAverage);
	}
	graph1->SetLineWidth(4);
	
	// Creates a second graph showing another moving average
	movingAverageRange = 5;
	movingAverageSteplength = 5;
	TGraph* graph2 = new TGraph();
	for(int bin = movingAverageRange; bin < numberOfYears-movingAverageRange; bin += movingAverageSteplength) {
		double movingAverage = 0;	
		for(int i = -movingAverageRange; i <= movingAverageRange; ++i){ 
			movingAverage += (averageTemp[bin+i]/(movingAverageRange*2+1));
		}	
		graph2->SetPoint(graph2->GetN(), histoRed->GetBinCenter(bin),movingAverage);
	}
	graph2->SetLineWidth(2);
		
	// The temperatures are actually focused around T = 0, so a new "fake" y-axis has to be constructed
	TGaxis *y_axis = new TGaxis(startYear,-4,startYear,4,-4+totAverage,4+totAverage,510);
	y_axis->SetName("y-axis");
		
	histoRed->GetYaxis()->SetBinLabel(1," ");	//removes old y-axis
	histoRed->SetMinimum(-4);
	histoRed->SetMaximum(4);
	histoRed->SetFillColor(2);
	histoBlue->SetFillColor(38);
	
	histoRed->Draw();
	histoBlue->Draw("Same");
	graph1->Draw("SAME C");
	graph2->Draw("SAME C");
	legend->Draw();
	y_axis->Draw();
	
	// Saves canvas on computer
	c1->SaveAs("global_warming.png");
}


