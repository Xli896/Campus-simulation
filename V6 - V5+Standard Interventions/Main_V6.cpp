#include <iostream>
#include<cmath>
#include"AllSchedule_V5.h"
#include"EverydaySchedule_V5.h"
#include"write_V5.h"
#include"StateTransition_V5.h"
#include"SamplingInfections_V5.h"
#include"TransmissionInfections_V5.h"
#include"Clear_V5.h"
#include"TestingProcess_V5.h"


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
	ClearEachRun();
	for (int i=0; i<Initial;i++)
	{
	    double RandomNumber = du(ge); //Randomly generate Patient Zero
	    AllStudents[(int)(RandomNumber*TNS)]->condition=1;
	    AllStudents[(int)(RandomNumber*TNS)]->SE=0;
	    CumuCase=CumuCase+1;
	}
	
	WriteDaySummaryIndividualHeader(k);
	WriteDaySummaryInv(CumuQua,CumuCase,CumuNumSym,0,Initial,k); 
	
	for(int i=0; i<NumberofWeeks;i++)    //NumberofWeeks: 14 weeks in a semester
	{
		for(int j=0;j<DaysoftheWeek;j++)    //DaysoftheWeek: 7 days in a week
		{
			int CountTest=0;
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
			vector<Student*> StudentHighTestPriority;
			vector<Student*> StudentMedTestPriority;
			vector<Student*> StudentLowTestPriority;
			
			//Update StudentInfected at the beginning of each day 
			for (Student* stu: AllStudents)
			{
				if ( (stu->ifOncampus==1) || (stu->NumClasses[SeqNum]!=0) )
				{
					if ( (stu->ifTested==0)&&(stu->ifWaitResult==0)&& (stu->ifQuarantine==0))
					{
						switch(stu->TestPriority)
						{
							    case 1:  { StudentLowTestPriority.push_back(stu);  break; }
							    case 2:  { StudentMedTestPriority.push_back(stu);  break; }
							    case 3:  { StudentHighTestPriority.push_back(stu); break; }
						}
					}
				}
				if((stu->condition==1)||(stu->condition==2)||(stu->condition==3)||(stu->condition==4)||(stu->condition==6))
				{
					StudentInfected.push_back(stu);
				}
			}
			StateTransition(StudentInfected,DayNum);
			
			//Update the result of testing each day
			for (Student* stu: AllStudents)
			{
				if ( stu->ifQuarantine==1 )
				{
					Quarantine(stu ,DayNum);
				}
				if ((stu->ifWaitResult==1) && (stu->ifTested==0)&& (stu->ifQuarantine==0))
				{
					TestingResult(stu ,DayNum);
				}
			}
			//Testing 3000 students according to the priority
			if (StudentHighTestPriority.size()>=NumTest){
				for (Student* stu: StudentHighTestPriority)
				{
					CountTest=CountTest+1;
					TestingProcess(stu ,DayNum);
					if (CountTest==NumTest) {break;}
				}

			}	
			else{
				if(StudentHighTestPriority.size()+StudentMedTestPriority.size()>=NumTest){
					for (Student* stu: StudentHighTestPriority)
					{
						CountTest=CountTest+1;
						TestingProcess(stu ,DayNum);
					}
					for (Student* stu: StudentMedTestPriority)
					{
						CountTest=CountTest+1;
						TestingProcess(stu ,DayNum);
						if (CountTest==NumTest) {break;}
					}
				}
				else{
					for (Student* stu: StudentHighTestPriority)
					{
						CountTest=CountTest+1;
						TestingProcess(stu ,DayNum);
					}
					for (Student* stu: StudentMedTestPriority)
					{
						CountTest=CountTest+1;
						TestingProcess(stu ,DayNum);
					}
					; 
					
				}
			}
			
						
			// Calculate the # infections on campus today
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
						    case 2:  
							{
								if(stu->ifQuarantine==0)
								{
									NumIP=NumIP+1;
								}
								break; 
							}
						    case 3:  
							{
								if(stu->ifQuarantine==0)
								{
									NumIA=NumIA+1;
								}
								break; 
							}
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
						    case 2:  
							{
								if(s->ifQuarantine==0)
								{
									NIp=NIp+1;
								}
								break; 
							}
						    case 3:  
							{
								if(s->ifQuarantine==0)
								{
									NIa=NIa+1;
								}
								break; 
							}
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
				    if ((stu->condition==0) && (stu->NumClasses[SeqNum]!=0) && (stu->ifQuarantine!=1)   )
				    {
				    	if( (bool) InclassInfections(stu,j,DayNum,SeqNum)) {NewExp+=1;CumuCase+=1;} 
				    }
			    }
			
				for (Student* stu:AllStudents)  //Outside of the class but on campus
				{
					if  ( (stu->condition==0)  && ((stu->ifOncampus==1)||(stu->NumClasses[SeqNum]!=0)) && (stu->ifQuarantine!=1)  )
					{
						if((bool) OutclassInfections(stu,j,DayNum,NumIP,NumIS,NumIA,SeqNum))  {NewExp+=1;CumuCase+=1;}
					}
				}
				
				for (Student* stu:AllStudents) //Off Campus
				{
					if  ((stu->condition==0)  && ((stu->ifOncampus==1)||(stu->NumClasses[SeqNum]!=0)) && (stu->ifQuarantine!=1) )
					{
						if((bool) OffCampusInfections(stu,j,DayNum,NumIP,NumIS,NumIA,SeqNum))  {NewExp+=1;CumuCase+=1;}
					}
				}
			}
			//Calculate new infections on Sunday (sample social activities)
			if (j==DaysoftheWeek-1)  // Calculate the infection on Weekends
			{
				vector<Student*> StudentSampledFrom;
				for (Student* stu:StudentsOnCampus)
				{
					if (stu->ifQuarantine==0)
					{
						StudentSampledFrom.push_back(stu);
					}
				}
				for (Student* stu:StudentSampledFrom)
				{
					if (stu->condition==0)  
					{
						if(SamplingInfectionsWeekends(stu,StudentSampledFrom,DayNum)) {NewExp+=1;CumuCase+=1;}	
					}
				}
			}
			WriteDaySummaryInv(CumuQua,CumuCase,CumuNumSym,DayNum,NewExp,k);    //Record summary of at the end of each day: # of students in different condition
			
		}
		

	}
}
WriteAverage();
}
