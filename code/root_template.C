// root_template.C
// 
// Johan Book
// 2017-11-01
//
// Plots an image of temperatures
//

// include C++ STL headers 
#include <iostream>
#include "treader.h"
#include "tpoint.h"

using namespace std;

// ROOT library obejcts
#include <TF1.h> // 1d function class
#include <TH1.h> // 1d histogram classes
#include <TStyle.h>  // style object
#include <TMath.h>   // math functions
#include <TCanvas.h> // canvas object

// Read and analyze part
void template_function(std::string path);

///////////////////////////////////////////////////////////////
// Source Code
//////////////////////////////////////////////////////////////

// Reads data and generates
void template_function(std::string path) 
{
	treader* tr = new treader(path);
	
	// Create histogram
	TH1D* histo = new TH1D("hV2", "Rooion; #varphi; Counts", 100, 0, 2*TMath::Pi());

	// Read from file while there is data to read
	while(tr->has_next())
	{
		// Get tpoint
		tpoint* tp = tr->get_tpoint();

		cout << tp->get_year() << "-" << tp->get_month() << "-" << tp->get_day() << " " << tp->get_temperature() << "\n";
	
		histo->Fill(tp->get_temperature());
	}
	
	
	// Set ROOT drawing styles
	gStyle->SetOptStat(1111);
	gStyle->SetOptFit(1111);

	// Create canvas for hPhi
	TCanvas* c1 = new TCanvas("c1", "v2 canvas", 900, 600);
	histo->SetMinimum(0);
	histo->Draw();

	// Save canvas as a picture
	c1->SaveAs("template_image.png");
}


