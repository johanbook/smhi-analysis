//Sara Gabrielli

#include <iostream>
#include <fstream>
#include <math.h> 

using namespace std;
int ndata; 
int y=0; //year counter

double Function_max(double tabella[][6], double Tmax_temporary,int nline), Function_min(double tabella[][6], double Tmax_temporary,int nline);
int NumberoutofDate(double table[][6],int nline);
int Date_Tmax[292], Date_Tmin[292];
int day_Tmax, day_Tmin;
double Arr_temporaryHot[2],Arr_temporaryCold[2];

// MAIN

	int main(){
	double table [106640][6];//ndata= total number of lines. 
	int nyears=292;//total number of years. E.g. for Uppsala is(2013-1722+1).
	double Tmax[nyears], Tmin[nyears];
	int Arr_year[nyears];
	int Arr_alltheyears[106640],Arr_allthedays[106640];
	double Arr_allthetemps[106640];
	double dummy1,dummy2;//dummy variable for finding the highest temperature of the year

	//Open and read file in table [6][ndata] bidimensional Array
	ifstream file("../data/Uppsala.dat");
	int yearNo,monthNo,dayNo,ID,year;
	double Temp, corrTemp;
	int count=0; //counter for while cycle
			
		while(file >> yearNo >> monthNo >>dayNo>> Temp>> corrTemp>>ID) {//read the data of Uppsala.dat into the bidimensional Array
		table[count][0]=yearNo;
		table[count][1]=monthNo;
		table[count][2]=dayNo;
		table[count][3]=Temp;
		table[count][4]=corrTemp;
		table[count][5]=ID;
		//cout<< table[count][0]<<" "<<table[count][5]<<endl; //test
		count++;
		ndata=count;
		//cout << ndata<<endl; //test
		}	
	// close file
	file.close();

	//Find the highest temperature for each year and collect it in the array Tmax[nyears]. 
	//Find also the day of the year corresponding to that temperature and collect it in the array date_Tmax[nyears].
	for(int i=0;i<106640;i++){
		if(table[i][0]==y+1722){
			dummy1 = Tmax[y];//dummy1= dummy variable. It is compared with the other temperatures in Function_max .
			dummy2=Tmin[y];
				if(table[i][5]==1){//it considers just the data from Uppsala (ID=1 in column 5)
					*Arr_temporaryHot=Function_max(table,dummy1,i);
					*Arr_temporaryCold=Function_min(table,dummy2,i);
				
					Tmax[y]=Arr_temporaryHot[0];//Tmax[nyears] contains the highest temperature for each year
					Date_Tmax[y]=Arr_temporaryHot[1];
					Arr_year[y]=1722+y;
					
					Tmin[y]=Arr_temporaryCold[0];
					Date_Tmin[y]=Arr_temporaryCold[1];}
		}
		else if(table[i][0]==y+1722+1){
		   y++;
		   dummy1=-20;
		   dummy2=+30;
				if(table[i][5]==1){	
					*Arr_temporaryHot=Function_max(table,dummy1,i);
					*Arr_temporaryCold=Function_min(table,dummy2,i);
					
					Tmax[y]=Arr_temporaryHot[0];
					Date_Tmax[y]=Arr_temporaryHot[1];
					Arr_year[y]=1722+y;
							
					Tmin[y]=Arr_temporaryCold[0];
					Date_Tmin[y]=Arr_temporaryCold[1];}
		}
	}

	for(int i=0;i<106640;i++){
		if(table[i][5]==1){
			Arr_alltheyears[i]=table[i][0];
			Arr_allthedays[i]=NumberoutofDate(table,i);
			Arr_allthetemps[i]=table[i][3];}
	}
	
	 // open output file1 and file2
	  ofstream file1("year_hotday_coldday.dat");
	  ofstream file2("years_days_temps.dat");
	
	for(int k=0; k<nyears;k++){//test
		file1<<Arr_year[k]<<" "<<Date_Tmax[k]<<" "<<Date_Tmin[k]<<" "<<endl;
	}
	  // close file1
	  file1.close();
	
	for(int k=0; k<106640;k++){//test
		file2<< Arr_alltheyears[k]<<" "<<Arr_allthedays[k]<<" "<<Arr_allthetemps[k]<<endl;
	}
	  // close file2
	  file2.close();
}

	//FUNCTIONS
	double Function_max(double table[][6], double Tmax_temporary,int nline){ 	//Function to obtain the highest temperature and the hottest day.
		if(table[nline][3]>Tmax_temporary){    //It goes through the temperature column
			Tmax_temporary = table[nline][3];
			day_Tmax = NumberoutofDate(table,nline);    
			Arr_temporaryHot[0]=Tmax_temporary;
			Arr_temporaryHot[1]=day_Tmax;
		}
		return *Arr_temporaryHot;
	}
	
		double Function_min(double table[][6], double Tmin_temporary,int nline){ 	//Function to obtain the lowes temperature and the coldest day.
		if(table[nline][3]<Tmin_temporary){    //It goes through the temperature column
			Tmin_temporary = table[nline][3];
			day_Tmin = NumberoutofDate(table,nline);    
			Arr_temporaryCold[0]=Tmin_temporary;
			Arr_temporaryCold[1]=day_Tmin;
		}
		return *Arr_temporaryCold;
	}

	int NumberoutofDate(double table[][6],int nline){   //It gives the number of the day from 1 to 366
		int day=0;
		
		if(table[nline][1]>1){      //adding the days of january
			day += 31;
		}
		if(table[nline][1]>2){      //adding the days of february
			if(table[nline][0]==2000){      //leap years must be taken into consideration!
				day += 28;
			}else if(fmod(table[nline][0],4.0)==0){
				day += 29;
			}else{
				day += 28;
			}
		}
		if(table[nline][1]>3){      //adding the days of march and so on
			day += 31;
		}
		if(table[nline][1]>4){      
			day += 30;
		}
		if(table[nline][1]>5){
			day += 31;
		}
		if(table[nline][1]>6){
			day += 30;
		}
		if(table[nline][1]>7){
			day += 31;
		}
		if(table[nline][1]>8){
			day += 31;
		}
		if(table[nline][1]>9){
			day += 30;
		}
		if(table[nline][1]>10){
			day += 31;
		}
		if(table[nline][1]>11){
			day += 30;
		}
		
		day += table[nline][2];
		
		return day;
}
