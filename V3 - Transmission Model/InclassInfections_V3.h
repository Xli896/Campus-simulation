#include <iostream>

using namespace std;
int InclassInfections(Student* stu,int j,int DayNum)
{ 
	int IfExp=0;
	bool ifSkip=0;  //to decide whether a student have been infected so need to skip the for loop
	for (Class* c:stu->InClass)
	{
	    if((c->NI!=0)&&(c->DayoftheWeek[j]==1)) 
	    {
	         double RandomNumber = du(ge);
             if(RandomNumber<=c->TranProb)  
             {
	            stu->condition=1;
	            stu->SE=DayNum+1;
				CumuCase=CumuCase+1;
				IfExp=1;
	            ifSkip=1;		
             }
	    }
	    if(ifSkip) {break;}
	}
	return IfExp;
}
