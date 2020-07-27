#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <map>
#include <string>
#include <sstream>
#include <random>

using namespace std;



bool WriteDayStudentMatrix(int DayNum) {
	DayStudent.open(outputfilename1,std::ios::app);
	DayStudent<<"Day"<<' '; DayStudent<<DayNum<<','; 
	for(int i=0; i<StudentVector.size();i++)
	{
		if (i!=StudentVector.size()-1) {DayStudent<<allStudent[StudentVector[i]]->condition<<',';}
		if (i==StudentVector.size()-1) {DayStudent<<allStudent[StudentVector[i]]->condition<<'\r';}
	}
	DayStudent.close();
	return 0;
}

bool WriteDaySummaryMatrix(int CumuNumSym,int DayNum,int NewExp) {
	
	int NumExp=0; //# Exposed
	int NumRec=0; //# Recovered
	int NumAsym=0; //# Asympotomatically Infected
	int NumSym=0; //# Sympotomatically Infected
	int NumHos=0; //# Hospitalization
	int NumDead=0; //# Dead
	

    for (auto it = allStudent.begin(); it != allStudent.end(); it++)
    {
	    switch(it->second->condition){
		    case 0:  {break;}
		    case 2:  {break;}
		    case 1:  {NumExp=NumExp+1;break;}
		    case 3:  {NumAsym=NumAsym+1;break;}
		    case 4:  {NumSym=NumSym+1;break;}
		    case 5:  {NumRec=NumRec+1;break;}
		    case 6:  {NumHos=NumHos+1;break;}
		    case 7:  {NumDead=NumDead+1;break;}
	    }
    }
    DaySummary.open(outputfilename2,std::ios::app);
    DaySummary<<"Day"<<' ';DaySummary<<DayNum<<',';
    DaySummary<<CumuNumSym<<',';
    DaySummary<<NumExp<<',';
    DaySummary<<NewExp<<',';
    DaySummary<<NumRec<<',';
    DaySummary<<NumAsym<<',';
    DaySummary<<NumSym<<',';
    DaySummary<<NumHos<<',';
    DaySummary<<NumDead<<'\r';
    DaySummary.close();
	return 0;
}
