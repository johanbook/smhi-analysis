//Sara Gabrielli

#include <iostream>
#include <fstream>
#include <vector>
#include <math.h> 
#include "Saracomplete.h"

using namespace std;
int ndata; 
int y=0; //year counter

//int date_maxT[292];


//class

Hottest::Hottest(double _table[106640][6], double _Tmax_temporanea,int _nriga)
{ table[106640][6]=_table[106640][6];
  Tmax_temporanea=_Tmax_temporanea;
  nriga=_nriga;}
Hottest::~Hottest(){}


//MAIN

	int main(){
		double table [106640][6];//ndata= total number of lines. 
		int nyears=292;//total number of years. E.g. for Uppsala is(2013-1722+1).
		double maxT[nyears];
		int arr_year[nyears];
		int line_maxT;
		double pippo;//dummy variable for finding the highest temperature of the year

		//Open and read file in table [6][ndata] bidimensional array
		ifstream file("../data/Uppsala.dat");
		int yearNo,monthNo,dayNo,ID,year;
		double Temp, corrTemp;
		int count=0; //counter for while cycle
			
		while(file >> yearNo >> monthNo >>dayNo>> Temp>> corrTemp>>ID) {//read the data of Uppsala.dat into the bidimensional array
			
			table[count][0]=yearNo;
			table[count][1]=monthNo;
			table[count][2]=dayNo;
			table[count][3]=Temp;
			table[count][4]=corrTemp;
			table[count][5]=ID;
			cout<< table[count][0]<<" "<<table[count][3]<<endl; //test
			//cout<<yearNo; //test
			count++;
			ndata=count;
			//cout << ndata<<endl; //test
			}
			
		// close file
		file.close();

		//Find the highest temperature for each year and collect it in the array maxT[nyears]. 
		//Find also the day of the year corresponding to that temperature and collect it in the array date_maxT[nyears].

		for(int i=0;i<106640;i++){
			if(table[i][0]==y+1722){
				pippo = maxT[y];//pippo= dummy variable. It is compared with the other temperatures in Function_maxT .
				Hottest Temp (table,maxT[y],i);
				Temp.Function_maxT();
				maxT[y]= Temp.GetTmax_temporanea();
				arr_year[y]=1722+y;
			}else if(table[i][0]==y+1722+1){
				y++;
				pippo = maxT[y];//pippo= dummy variable. It is compared with the other temperatures in Function_maxT .
				Hottest Temp (table,maxT[y],i);
				Temp.Function_maxT();
				maxT[y]= Temp.GetTmax_temporanea();
				arr_year[y]=1722+y;
			}
		}
		
		
		for(int k=0; k<nyears;k++){//test
			cout<<maxT[k]<<" "<<arr_year[k]<<" "<<endl;
		}
	}

	
