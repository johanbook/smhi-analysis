// global_warming.C
// 
// Edvin Jakobsson
// MNXB01 project 
// 2017-11-06
//
// 
//

// include C++ STL headers that are used to read the data
#include <iostream>
#include <fstream>
#include "treader.h"
#include "tpoint.h"

using namespace std;

// ROOT library objects
#include <TF1.h> // 1d function class
#include <TH1.h> // 1d histogram classes
#include <TStyle.h>  // style object
#include <TMath.h>   // math functions
#include <TCanvas.h> // canvas object



// Reads data and generates
void global_warming_function(string path) {
	
	int startYear = 1722;
	int endYear = 2013;
	double yay[endYear-startYear];
	
	treader* tr = new treader(path);
	
			// Create histogram
	//TH1D* histo = new TH1D("hV2", "Rooion; #varphi; Counts", 100, 0, 2*TMath::Pi());
	
	double temperatureSum = 0;
	int numberOfPoints = 0;
	double temporarySave = 0;
	double totalSum = 0;
		
	for(int i = startYear; i<=endYear; ++i){

		// Read from file while there is data to read
		while(tr->has_next())
		{	
			// Get tpoint
			tpoint* tp = tr->get_tpoint();

			if (tp->get_year() != i){
				temporarySave = tp->get_temperature();
				break;
			}

			++numberOfPoints;
			//cout << tp->get_year() << "-" << tp->get_month() << "-" << tp->get_day() << " " << tp->get_temperature() << "\n";
	
			temperatureSum += tp->get_temperature();
			
			//histo->Fill(tp->get_temperature());
		}
		cout << i << "\t Avg temp: " << temperatureSum/numberOfPoints << "\t total average: " << totalSum/(i-startYear) << endl;

		totalSum += temperatureSum/numberOfPoints;
		temperatureSum = temporarySave;
		numberOfPoints = 1;
	}
	

	
			// Set ROOT drawing styles
	//gStyle->SetOptStat(1111);
	//gStyle->SetOptFit(1111);

			// Create canvas for hPhi
	//TCanvas* c1 = new TCanvas("c1", "v2 canvas", 900, 600);
	//histo->SetMinimum(0);
	//histo->Draw();

			// Save canvas as a picture
	//c1->SaveAs("template_image.png");
}

/*
int main(){
	
	cout << "heJ" << endl;
	
	return 0;
	
}
*/

