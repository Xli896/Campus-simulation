#include <iostream>
#include"Sample_V2.h"

using namespace std;

int SamplingInfectionsInClass(int N, Student* stu, vector<Class*>& ClassSuc,int j,int DayNum)
{ 
    int IfExp=0;
	bool ifSkip=0;  //to decide whether a student have been infected so need to skip the for loop
    for (Class* c:stu->InClass)
    {
	    if((c->NI!=0)&&(c->DayoftheWeek[j]==1)) 
	    {
	        vector<int>* p;
            int NSample;
	        int NumofThisStu=FindIndex_1(classStudentMap[c], stu);  //find the index of stu in the vector<Student*> for class c
            if (classStudentMap[c].size()>N) {NSample=N;}
	        if (classStudentMap[c].size()<=N) {NSample=classStudentMap[c].size()-1;}  
            p=Sample(NSample,0,classStudentMap[c].size(),NumofThisStu);	        // generate 6 different students in the class 
	        for (int i=0;i<NSample;i++)     
	        {
		        switch (classStudentMap[c][p->at(i)]->condition)       
		        {
			        case 0:  {break;}
			        case 1:  {break;}
			        case 5:  {break;}
			        case 6:  {break;}
			        case 7:  {break;}
			        case 2:  {
				         double RandomNumber = du(ge);
			             if(RandomNumber<=Pp)  
			             {
				            stu->condition=1;
				            stu->SE=DayNum+1;
                            CumuCase=CumuCase+1;
                            IfExp=1;
				            ifSkip=1;
			             }
				         break;
				    }
			        case 3:  {
				         double RandomNumber = du(ge);
			             if(RandomNumber<=Pa)  
			             {
				            stu->condition=1;
				            stu->SE=DayNum+1;
                            CumuCase=CumuCase+1;
                            IfExp=1;
				            ifSkip=1;
			             }
				         break;
				    }
			        case 4:  {
				         if(classStudentMap[c][p->at(i)]->ifQuarantine) {break;}
				         if(!classStudentMap[c][p->at(i)]->ifQuarantine){
					         double RandomNumber = du(ge);
				             if(RandomNumber<=Ps)  
				             {
					            stu->condition=1;
					            stu->SE=DayNum+1;
                                CumuCase=CumuCase+1;
                                IfExp=1;
					            ifSkip=1;
				             }
					         break;
				         }
				    }
			    } 
			    if(ifSkip) {break;}  
	        }
	    }
	    if(ifSkip) {break;}
    }
	return IfExp;
}

int SamplingInfectionsWeekends(Student* stu,vector<int>& StudentVector,int DayNum)
{   
            int IfExp=0;
            int NW;
	        bool ifSkip=0;  //to decide whether a student have been infected so need to skip the for loop
	        vector<int>* p;
	        int NumofThisStu=FindIndex_2(StudentVector, stu->studentID);  //find the index of stu in the vector<Student*> for class c
            double RandomNumber = du(ge);
            if(RandomNumber<=PGreekLife)  {NW=NW_H;}
            if(RandomNumber>PGreekLife)  {NW=NW_L;}
	        p=Sample(NW,0,StudentVector.size(),NumofThisStu);  // generate NW different students during weekends (can not be this stu)
	        for (int i=0;i<NW;i++)     
	        {
		        switch (allStudent[ StudentVector[p->at(i)] ]->condition)       
		        {
			        case 0:  {break;}
			        case 1:  {break;}
			        case 5:  {break;}
			        case 6:  {break;}
			        case 7:  {break;}
			        case 2:  {
				         double RandomNumber = du(ge);
			             if(RandomNumber<=Pp)  
			             {
				            stu->SE=DayNum+1;
                            CumuCase=CumuCase+1;
                            stu->condition=1;
                            IfExp=1;
				            ifSkip=1;
			             }
				         break;
				    }
			        case 3:  {
				         double RandomNumber = du(ge);
			             if(RandomNumber<=Pa)  
			             {
				            stu->SE=DayNum+1;
                            CumuCase=CumuCase+1;
                            stu->condition=1;
                            IfExp=1;
				            ifSkip=1;
			             }
				         break;
				    }
			        case 4:  {
				         if(allStudent[ StudentVector[p->at(i)] ]->ifQuarantine) {break;}
				         if(!allStudent[ StudentVector[p->at(i)] ]->ifQuarantine){
					         double RandomNumber = du(ge);
				             if(RandomNumber<=Ps)  
				             {
					            stu->SE=DayNum+1;
                                CumuCase=CumuCase+1;
                                stu->condition=1;
                                IfExp=1;
					            ifSkip=1;
				             }
					         break;
				         }
				    }
			    } 
			    if(ifSkip) {break;}  
	        }
	return IfExp;
}
