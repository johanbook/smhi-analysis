#include <iostream>
using namespace std;

class Hottest {
	public:
	Hottest (double *table, double _Tmax_temporanea,int _nriga);
	~Hottest();
	//double Function_maxT(double table[][106640], int *giorno, double Tmax_temporanea,int nriga){   //It takes into consideration the whole array
	
	void Function_maxT(){ 	
		if(table[nriga][3]>Tmax_temporanea){    //It goes through the Temperature column
			Tmax_temporanea = table[nriga][3];
			cout<<table[nriga][3]<<" "<<Tmax_temporanea<<" "<<nriga<<endl;
			//date_maxT = Numberoutofdate(table,nriga);    //It updates the date through pointer
		}
	;}
	
	double GetTmax_temporanea(){return Tmax_temporanea;}
		
	private: 
	double table[][6];
	double Tmax_temporanea;
	int nriga;
	};

	//int Numberoutofdate(double table[][106640],int nriga){   //estrae il numero del giorno
		//int giorno=-1;
		
		//if(table[nriga][1]>1){      //adding the days of january
			//giorno += 31;
		//}
		//if(table[nriga][1]>2){      //adding the days of february
			//if(table[nriga][0]==2000){      //leap years must be taken into consideration!
				//giorno += 28;
			//}else if(fmod(table[nriga][0],4.0)==0){
				//giorno += 29;
			//}else{
				//giorno += 28;
			//}
		//}
		//if(table[nriga][1]>3){      //adding the days of march and so on
			//giorno += 31;
		//}
		//if(table[nriga][1]>4){      
			//giorno += 30;
		//}
		//if(table[nriga][1]>5){
			//giorno += 31;
		//}
		//if(table[nriga][1]>6){
			//giorno += 30;
		//}
		//if(table[nriga][1]>7){
			//giorno += 31;
		//}
		//if(table[nriga][1]>8){
			//giorno += 31;
		//}
		//if(table[nriga][1]>9){
			//giorno += 30;
		//}
		//if(table[nriga][1]>10){
			//giorno += 31;
		//}
		//if(table[nriga][1]>11){
			//giorno += 30;
		//}
		
		//giorno += table[nriga][2];
		
		//return giorno;
	//}

