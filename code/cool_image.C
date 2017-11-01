// Analyze_v2.C
// 
// Homework 7b
// Johan Book
// 2017-10-27
//

// include C++ STL headers 
#include <iostream>
#include <fstream>

using namespace std;

// ROOT library obejcts
#include <TF1.h> // 1d function class
#include <TH1.h> // 1d histogram classes
#include <TStyle.h>  // style object
#include <TMath.h>   // math functions
#include <TCanvas.h> // canvas object

// Read and analyze part
void analyze_v2_2particle();

// Calculates <2> from a Double_t array using the Standard Method
Double_t c2_standard(Double_t *phi, Int_t nTracks);

// Calculates <2> from a Double_t array using Q-vectors
Double_t c2_Qvector(Double_t *phi, Int_t nTracks);

// Caclulates v2 for a given value of <2>
Double_t extract_v2(Double_t c2){ return TMath::Sqrt(TMath::Abs(c2));}

///////////////////////////////////////////////////////////////
// Source Code
//////////////////////////////////////////////////////////////

// Analyze data in file phi_dist.day and calculate v2
void analyze_v2_2particle() 
{
	Int_t nEvents = 0;
	Double_t mean_nTracks = 0;
	string helpString; //dummy string

	// Open input file
	ifstream file("phi_dist.dat");
	Int_t eventNo = -1;

	// Store <2> info
	Double_t sum_c2 = 0;
	Double_t sum_c2_Q = 0;

	// Create histogram
	TH1D* hPhi = new TH1D("hV2", "Root func generated v2 distribution; #varphi; Counts", 100, 0, 2*TMath::Pi());

	// Read from file while there is data to read
	while(file >> helpString >> eventNo)
	{
		nEvents++;
		
		Int_t nTracks = -1;
		file >> helpString >> nTracks;
		mean_nTracks += nTracks;

		// Declare array
		Double_t* phi = new Double_t[nTracks];

		// Read data into array
		for(Int_t nt = 0; nt < nTracks; nt++)
		{	
			file >> helpString >> helpString >> phi[nt];
			hPhi->Fill(phi[nt]);
		}

		// Print v2 estimates
		sum_c2 += c2_standard(phi, nTracks);
		sum_c2_Q += c2_Qvector(phi, nTracks);
		
		// Delete dynamic array to release memory
		delete phi;
	}
	
	// Print general info
	mean_nTracks /= nEvents;
	cout << "Number of events: " << nEvents << "\n";
	cout << "Mean number of tracks: " << mean_nTracks << "\n"; 
	
	// Calculate and print mean v2
	Double_t mean_c2 = sum_c2 / nEvents;
	Double_t mean_c2_Q = sum_c2_Q / nEvents;
	cout << "\nResult:\n";
	cout << "v2 (average of " << nEvents << " events) = " << extract_v2(mean_c2) << "\n";
	cout << "Q: v2 (average of " << nEvents << " events) = " << extract_v2(mean_c2_Q) << "\n";

	// Set ROOT drawing styles
	gStyle->SetOptStat(1111);
	gStyle->SetOptFit(1111);

	// Create canvas for hPhi
	TCanvas* c1 = new TCanvas("c1", "v2 canvas", 900, 600);
	hPhi->SetMinimum(0);
	hPhi->Draw();

	// Save canvas as a picture
	c1->SaveAs("v2_rootfunc.png");
}

// Calculate v2 using the standard method 
Double_t c2_standard(Double_t *phi, Int_t nTracks)
{
	Double_t sum_cos2_diff = 0;
	Int_t num = 0;
	
	for(Int_t i = 0; i < nTracks; i++)
		for(Int_t j = i+1; j < nTracks; j++, num++)
			sum_cos2_diff += 2*TMath::Cos(2*(phi[i] - phi[j]));
	
	return sum_cos2_diff/(2*num);
}

// Calculate v2 using Q vectors
Double_t c2_Qvector(Double_t *phi, Int_t nTracks)
{
	// Q vector
	Double_t sum_cos2 = 0;
	Double_t sum_sin2 = 0;

	// Compute Q vector
	for(Int_t i = 0; i < nTracks; i++)
	{
		sum_cos2 += TMath::Cos(2*phi[i]);
		sum_sin2 += TMath::Sin(2*phi[i]);
	}

	Double_t Q2 = sum_cos2*sum_cos2 + sum_sin2*sum_sin2;
	return (Q2 - nTracks)/(nTracks*(nTracks - 1));
}
