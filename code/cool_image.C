// cool_image.C
// 
// Johan Book
// 2017-10-27
//
// Plots an image
//

// include C++ STL headers 
#include <iostream>
#include <fstream>
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
void generate_image(std::string path);

///////////////////////////////////////////////////////////////
// Source Code
//////////////////////////////////////////////////////////////

// Reads data and generates
void generate_image(std::string path) 
{
	treader* tr = new treader(path);
	
	// Create histogram
	TH1D* hPhi = new TH1D("hV2", "Rooion; #varphi; Counts", 100, 0, 2*TMath::Pi());

	// Read from file while there is data to read
	//while(tr->has_next())
	{
		//cout << tr->get_tpoint()->get_year() << "\n";
	}
	
	
	// Set ROOT drawing styles
	gStyle->SetOptStat(1111);
	gStyle->SetOptFit(1111);

	// Create canvas for hPhi
	TCanvas* c1 = new TCanvas("c1", "v2 canvas", 900, 600);
	hPhi->SetMinimum(0);
	hPhi->Draw();

	// Save canvas as a picture
	c1->SaveAs("cool_image.png");
}


