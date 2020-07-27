#include <iostream>
#include<cmath>
#include"AllSchedule_V5.h"
#include"EverydaySchedule_V5.h"
#include"write_V5.h"
#include"StateTransition_V5.h"
#include"SamplingInfections_V5.h"
#include"TransmissionInfections_V5.h"
#include"Clear_V5.h"


int main() {
    filenameAM.push_back("AffiliationMatrix_M.csv");
    filenameAM.push_back("AffiliationMatrix_T.csv");
    filenameAM.push_back("AffiliationMatrix_W.csv");
    filenameAM.push_back("AffiliationMatrix_R.csv");
    filenameAM.push_back("AffiliationMatrix_F.csv");
    filenameAM.push_back("AffiliationMatrix_S.csv");
    OpenFiles() ; //Read the total AffiliationMatrix and save the data
    int NumberData=0;
	for(int i=0; i<4;i++)    //NumberofWeeks: 14 weeks in a semester
	{
		for(int j=0;j<DaysoftheWeek-1;j++)    //DaysoftheWeek: 7 days in a week
		{
			OpenEverydayFile(filenameAM[j],i,NumberData);
			NumberData=NumberData+1;
		}
	}
    WriteAverageHeader();

for(int k=0;k<RunTimes;k++)	
{
	cout<<"Run"<<" "; cout<<k<<endl;
	if(k!=0) {ClearEachRun();}
	for (int i=0; i<Initial;i++)
	{
	    double RandomNumber = du(ge); //Randomly generate Patient Zero
	    AllStudents[(int)(RandomNumber*TNS)]->condition=1;
	    AllStudents[(int)(RandomNumber*TNS)]->SE=0;
	    CumuCase=CumuCase+1;
	}
	
	WriteDaySummaryIndividualHeader(k);
	WriteDaySummaryInv(CumuCase,CumuNumSym,0,Initial,k); 
	
	for(int i=0; i<NumberofWeeks;i++)    //NumberofWeeks: 14 weeks in a semester
	{
		for(int j=0;j<DaysoftheWeek;j++)    //DaysoftheWeek: 7 days in a week
		{
			int SeqNum=100;   //using the data with sequence number SeqNum
			int DayNum=7*i+j+1;//the number of that day 
			ClearEachDay();
			cout<<"day:"<<" "; cout<<DayNum<<endl;
			if(j!=DaysoftheWeek-1)  
			{ 
				SeqNum=(i%4)*6+j;
				for (Student* stu: AllStudents)
				{
					for (Class* cla: stu->InClassToday[SeqNum])
					{
						ClassStudentsTodayMap[cla].push_back(stu);
					}
				}
			}
			int NewExp=0; //#New Exposed
			int NumIP=0;
			int NumIS=0;
			int NumIA=0;
			vector<Student*> StudentInfected; //Record students those have been exposed/infected and haven't recovered/Dead:  E,Ip,Ia,Is,Ih calculate transitions
			//Update StudentInfected at the beginning of each day 
			for (Student* stu: AllStudents)
			{
				if((stu->condition==1)||(stu->condition==2)||(stu->condition==3)||(stu->condition==4)||(stu->condition==6))
				{
					StudentInfected.push_back(stu);
				}
			}
			StateTransition(StudentInfected,DayNum);
			for (Student* stu: AllStudents)
			{
				if ((stu->ifOncampus==1)||(stu->NumClasses[SeqNum]!=0))
				{
					switch(stu->condition){
						    case 0:  {break;}
						    case 1:  {break;}
						    case 5:  {break;}
						    case 6:  {break;}
						    case 7:  {break;}
						    case 2:  {NumIP=NumIP+1;break;}
						    case 3:  {NumIA=NumIA+1;break;}
						    case 4:  
							{
								if(stu->ifQuarantine==0)
								{
									NumIS=NumIS+1;
								}
								break; 
							}
					}
				}
			}
			//Calculate new infections during WeekDay (have classes on campus)
			if(j!=DaysoftheWeek-1) 
			{
				// Update TranRate & TranProb for each class
				for (Class* cla:ClassesToday[SeqNum]) 
			    {
				    int NIs=0;
					int NIp=0;
					int NIa=0;
					for (Student* s:ClassStudentsTodayMap[cla]) 
					{
					    switch(s->condition){
						    case 0:  {break;}
						    case 1:  {break;}
						    case 5:  {break;}
						    case 6:  {break;}
						    case 7:  {break;}
						    case 2:  {NIp=NIp+1;break;}
						    case 3:  {NIa=NIa+1;break;}
						    case 4:  
							{
								if(s->ifQuarantine==0)
								{
									NIs=NIs+1;
								}
								break; 
							}
					    }
					}
					cla->TranRate=lambda_s*NIs+lambda_p*NIp+lambda_a*NIa; 
					cla->TranProb=1-exp(-cla->TranRate);
			    }
			    //For each susceptible student, decide whether she/he will get infected today
			    for (Student* stu:AllStudents)  //In class infections
			    {
				    if ((stu->condition==0) && (stu->NumClasses[SeqNum]!=0))
				    {
				    	if( (bool) InclassInfections(stu,j,DayNum,SeqNum)) {NewExp+=1;CumuCase+=1;} 
				    }
			    }
			
				for (Student* stu:AllStudents)  //Outside of the class but on campus
				{
					if  ( (stu->condition==0)  && ((stu->ifOncampus==1)||(stu->NumClasses[SeqNum]!=0)) )
					{
						if((bool) OutclassInfections(stu,j,DayNum,NumIP,NumIS,NumIA,SeqNum))  {NewExp+=1;CumuCase+=1;}
					}
				}
				
				for (Student* stu:AllStudents) //Off Campus
				{
					if  ((stu->condition==0)  && ((stu->ifOncampus==1)||(stu->NumClasses[SeqNum]!=0)))
					{
						if((bool) OffCampusInfections(stu,j,DayNum,NumIP,NumIS,NumIA,SeqNum))  {NewExp+=1;CumuCase+=1;}
					}
				}
			}
			
			if (j==DaysoftheWeek-1)  // Calculate the infection on Weekends
			{
				for (Student* stu:AllStudents)
				{
					if ((stu->condition==0) && (stu->ifOncampus==1))  
					{
						if(SamplingInfectionsWeekends(stu,StudentsOnCampus,DayNum)) {NewExp+=1;CumuCase+=1;}	
					}
				}
			}
			WriteDaySummaryInv(CumuCase,CumuNumSym,DayNum,NewExp,k);    //Record summary of at the end of each day: # of students in different condition
			
		}
		

	}
}
WriteAverage();
}
