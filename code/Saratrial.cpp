//Sara Gabrielli

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;
int ndata; 

double Function_maxT(double tabella[][ndata], int *giorno, double Tmax_temporanea,int nriga);
int Numberoutofdate(double**table,int nriga);

//MAIN
int main(){
double table [6][ndata];//ndata= total number of lines. 
int nyears;//total number of years. E.g. for Uppsala is(2013-1722+1).
double maxT[nyears];
int date_maxT[nyears];
double pippo;//dummy variable for finding the highest temperature of the year
int y=0; //year counter

//double Function_maxT(double, int, double,int );//finds the max temperature
//int Numberoutofdate(double,int);// returns the number of the day (from 1 to 365)

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
	//cout<< table[count][0]<<" "<<table[count][3]<<endl; test
	//cout<<yearNo; test
	count++;
	ndata=count;
	//cout << ndata<<endl; test
	}
	
// close file
file.close();

//Find the highest temperature for each year and collect it in the array maxT[nyears]. 
//Find also the day of the year corresponding to that temperature and collect it in the array date_maxT[nyears].

for(int i=0;i<ndata;i++){
    if(table[i][0]==y+1722){
        pippo = maxT[y];//pippo= dummy variable. It is compared with the other temperatures in Function_maxT .
        maxT[y]=Function_maxT(table,date_maxT,maxT[y],i);// date_maxT is the pointer to the array, do not confuse it with date_maxT[y]!
    }else if(table[i][0]==y+1722+1){
        y++;
        maxT[y]=Function_maxT(table,date_maxT,maxT[y],i);
    }else{
        cout<<"error:1 year missing in the data file"<<endl;//error message if one year is missing in the data file
    }    
}
}

double Function_maxT(double table[][ndata], int *giorno, double Tmax_temporanea,int nriga){   //It takes into consideration the whole array
    if(table[nriga][3]>Tmax_temporanea){    //It goes through the Temperature column
        Tmax_temporanea = table[nriga][3];
        date_maxT[y] = Numberoutofdate(table,nriga);    //It updates the date through pointer
    }
    return Tmax_temporanea;
}

int Numberoutofdate(double table[][ndata],int nriga){   //estrae il numero del giorno
    int giorno=-1;
    
    if(table[nriga][1]>1){      //adding the days of january
        giorno += 31;
    }
    if(table[nriga][1]>2){      //adding the days of february
        if(table[nriga][0]==2000){      //leap years must be taken into consideration!
            giorno += 28;
        }else if(table[nriga][0]%4==0){
            giorno += 29;
        }else{
            giorno += 28;
        }
    }
    if(table[nriga][1]>3){      //adding the days of march and so on
        giorno += 31;
    }
    if(table[nriga][1]>4){      
        giorno += 30;
    }
    if(table[nriga][1]>5){
        giorno += 31;
    }
    if(table[nriga][1]>6){
        giorno += 30;
    }
    if(table[nriga][1]>7){
        giorno += 31;
    }
    if(table[nriga][1]>8){
        giorno += 31;
    }
    if(table[nriga][1]>9){
        giorno += 30;
    }
    if(table[nriga][1]>10){
        giorno += 31;
    }
    if(table[nriga][1]>11){
        giorno += 30;
    }
    
    giorno += table[nriga][2];
    
    return giorno;
}
