//name: Sara Gabrielli

// include C++ STL headers 
#include <iostream>

using namespace std;

// ROOT library obejcts
#include <TF1.h> // 1d function class
#include <TH1.h> // 1d histogram classes
#include <TStyle.h>  // style object
#include <TMath.h>   // math functions
#include <TCanvas.h> // canvas object
#include <fstream>

void func();

void func(){
	Int_t nline = 1; // line counter
	string helpString,helpString1,helpString2,helpString3,helpString4; // help variable
	//open file
	ifstream file("../data/Uppsala.dat");
	Int_t yearNo,monthNo,dayNo,ID;
	Double_t Temp, corrTemp;
	
	while(file >> yearNo >> monthNo >>dayNo>> Temp>> corrTemp>>ID) {
		//The following lines are to verify the code has been read correctly
		//cout << "Reading line : " << nline << endl; 
		//cout<< yearNo<<" "<<monthNo<<" "<<Temp<<" "<<corrTemp<<" "<< ID<<endl<<endl;
		//nline++;
		if(ID!=1){}
		else
		}
	
	// close file
	file.close();
	
}
