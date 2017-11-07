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
#include <TGaxis.h>
#include <TLegend.h>
#include <TGraph.h>



// Reads data and generates
void global_warming_function(string path) {
	
	int startYear = 1722;
	int endYear = 2013;
	int numberOfYears = endYear-startYear+1;
		
	treader* tr = new treader(path);
	
	double temperatureSum = 0;
	int numberOfPoints = 0;
	double temporarySave = 0;
	double totalSum = 0;
	Double_t averageTemp[numberOfYears];
	Double_t year[numberOfYears];
		
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
		//cout << i << "\t Avg temp: " << temperatureSum/numberOfPoints << "\t total average: " << totalSum/(i-startYear) << endl;
		year[i-startYear] = i;
		averageTemp[i-startYear] = temperatureSum/numberOfPoints;

		totalSum += temperatureSum/numberOfPoints;
		temperatureSum = temporarySave;
		numberOfPoints = 1;
	}
	
	double totAverage = 0;
	
	for(int i = 0; i <(numberOfYears); ++i){
		totAverage += averageTemp[i]/numberOfYears;
	}



			// Create canvas
	TCanvas* c1 = new TCanvas("c1", "v2 canvas", 900, 600);
	
	// Create histogram
	TH1F* histoRed = new TH1F("hV2", "Rooion; Year; Temperature [#circ C]",numberOfYears , startYear, endYear);	
	TH1F* histoBlue = new TH1F("hV2", "Rooion; #varphi; Counts",numberOfYears , startYear, endYear);
	TH1F* histoTot = new TH1F("hV2", "Rooion; #varphi; Counts",numberOfYears , startYear, endYear);
	
	
	for(int i = 0; i<numberOfYears; ++i){
		double temp = averageTemp[i] - totAverage;
		histoTot->SetBinContent(i,temp);
		if(temp >= 0)
			histoRed->SetBinContent(i,temp);
		else
			histoBlue->SetBinContent(i,temp);	
		}	
		
	TLegend *leg = new TLegend(0.65, 0.80, 0.94, 0.94, "", "NDC");
	leg->SetFillStyle(0); //Hollow fill (transparent)
	leg->SetBorderSize(0); //Get rid of the border
	leg->AddEntry(histoRed, "Above average temperature", "F"); //Use object title, draw fill
	leg->AddEntry(histoBlue, "Below average temperature", "F"); //Use custom title	
	
	int movingAverageRange = 20;
	int movingAverageSteplength = 10;
	
	TGraph* graph = new TGraph();
	for(int bin = 1; bin < histoTot->GetNbinsX(); bin += movingAverageSteplength) {
		double y = 0;
		
		for(int i = -movingAverageRange; i <= movingAverageRange; ++i) 
			y += (histoTot->GetBinContent(bin+i)/(movingAverageRange*2+1));
		
		graph->Expand(graph->GetN() + 1, 100);
		graph->SetPoint(graph->GetN(), histoTot->GetBinCenter(bin),y);
	}
			
	histoRed->GetYaxis()->SetBinLabel(1," ");
	histoRed->SetMinimum(-4);
	histoRed->SetMaximum(4);
	histoRed->SetFillColor(2);
	histoBlue->SetFillColor(4);
	histoRed->Draw();
	histoBlue->Draw("Same");

	TGaxis *axis2 = new TGaxis(1722,-4,1722,4,-4+totAverage,4+totAverage,510);
	axis2->SetName("axis2");
	axis2->Draw();
	leg->Draw();
	
	graph->SetLineWidth(3);
	graph->Draw("SAME C");
	
			// Save canvas as a picture
	c1->SaveAs("global_warming.png");
}


