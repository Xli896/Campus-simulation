#include <iostream>
#include<cmath>
#include"Openclassfile.h"
#include"write.h"
#include"StateTransition.h"
#include"SamplingInfections.h"
#include"InclassInfections.h"


int main() {
    filenameAM.push_back("AffiliationMatrix_M.csv");
    filenameAM.push_back("AffiliationMatrix_T.csv");
    filenameAM.push_back("AffiliationMatrix_W.csv");
    filenameAM.push_back("AffiliationMatrix_R.csv");
    filenameAM.push_back("AffiliationMatrix_F.csv");
    filenameAM.push_back("AffiliationMatrix_S.csv");
    filenameAM.push_back("AffiliationMatrix.csv");
    for(int i=filenameAM.size()-1;i>=0;i--) {Openclassfile(filenameAM[i],i);} //Read AffiliationMatrix and save the data

for(int k=0;k<RunTimes;k++)	
{
	cout<<"Run"<<" "; cout<<k<<endl;
	if(k!=0) {ClearAll();}
	for (int i=0; i<Initial;i++)
	{
	    double RandomNumber = du(ge); //Randomly generate Patient Zero
	    allStudent[StudentVector[(int)(RandomNumber*NS)]]->condition=1;  
	    allStudent[StudentVector[(int)(RandomNumber*NS)]]->SE=0;
	    CumuCase=CumuCase+1;
	}
	
	WriteDaySummaryIndividualHeader(k);
	WriteDaySummary(CumuCase,CumuNumSym,0,Initial,k); 
	
	
	for(int i=0; i<NumberofWeeks;i++)    //NumberofWeeks: 14 weeks in a semester
	{
		for(int j=0;j<DaysoftheWeek;j++)    //DaysoftheWeek: 7 days in a week
		{
			int DayNum=7*i+j+1;//the number of that day 
			cout<<"day:"<<" "; cout<<DayNum<<endl;
			int NewExp=0; //#New Exposed
			int NumIP=0;
			int NumIS=0;
			int NumIA=0;
			vector<Student*> StudentInfected; //Record students those have been exposed/infected and haven't recovered/Dead:  E,Ip,Ia,Is,Ih calculate transitions
			//Update StudentInfected at the beginning of each day 
			for (auto it = allStudent.begin(); it != allStudent.end(); it++)
			{
				switch(it->second->condition){
					    case 0:  {break;}
					    case 1:  {StudentInfected.push_back(it->second);break;}
					    case 5:  {break;}
					    case 6:  {StudentInfected.push_back(it->second);break;}
					    case 7:  {break;}
					    case 2:  {StudentInfected.push_back(it->second);NumIP=NumIP+1;break;}
					    case 3:  {StudentInfected.push_back(it->second);NumIA=NumIA+1;break;}
					    case 4:  
						{
							StudentInfected.push_back(it->second);
							if(it->second->ifQuarantine==0)
							{
								NumIS=NumIS+1;
							}
							break; 
						}
				}
			}
			StateTransition(StudentInfected,DayNum);
			//Calculate new infections during WeekDay (have classes on campus)
			if(j!=DaysoftheWeek-1) 
			{
				vector<Class*> ClassSuc; //Susceptible class with infected student (not quarantine) at that day
				vector<Student*> StudentSucIn; //Students those taking classes together with infected student  (not quarantine) at that day
				// Update ClassSuc (class with infectious students) & StudentSuc (susceptible students)
				for (auto it = allClass.begin(); it != allClass.end(); it++) 
			    {
				    if((it->second->DayoftheWeek[j]==1)&&(it->second->NI!=0))
					{
						for (Student* s:classStudentMap[it->second]) 
						{
							if((s->condition==0) && (std::find(StudentSucIn.begin(), StudentSucIn.end(), s) == StudentSucIn.end())  )  {StudentSucIn.push_back(s);}
						}
					    ClassSuc.push_back(it->second);
					    int NIs=0;
						int NIp=0;
						int NIa=0;
						for (Student* s:classStudentMap[it->second]) 
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
						it->second->TranRate=lambda_s*NIs+lambda_p*NIp+lambda_a*NIa; 
						it->second->TranProb=1-exp(-it->second->TranRate);
				    }
			    }
			    //For each susceptible student, decide whether she/he will get infected today
			    if (StudentSucIn.size()!=0)  //In class
			    {
				    for (Student* stu:StudentSucIn)
				    {
					    if( (bool) InclassInfections(stu,j,DayNum)) {NewExp+=1;CumuCase+=1;} 
				    }
			    }
				for (auto it = allStudent.begin(); it != allStudent.end(); it++)  //Outside of the class but on campus
				{
					if(it->second->condition==0)  
					{
						if((bool) OutclassInfections(it->second,j,DayNum,NumIP,NumIS,NumIA))  {NewExp+=1;CumuCase+=1;}
					}
				}
				for (auto it = allStudent.begin(); it != allStudent.end(); it++) //Off Campus
				{
					if(it->second->condition==0)  
					{
						if((bool) OffCampusInfections(it->second,j,DayNum,NumIP,NumIS,NumIA))  {NewExp+=1;CumuCase+=1;}
					}
				}
			}
			
			if (j==DaysoftheWeek-1||j==DaysoftheWeek-2)  // Calculate the infection on Weekends
			{
				vector<Student*> StudentSuc; //Students those taking classes together with infected student  (not quarantine) at that day
				for (auto it = allStudent.begin(); it != allStudent.end(); it++) 
				{
					if(it->second->condition==0)   
					{
						if(SamplingInfectionsWeekends(it->second,StudentVector,DayNum))
						{
							NewExp+=1;
							CumuCase+=1;
						}	
					}
				}
			}
			WriteDaySummary(CumuCase,CumuNumSym,DayNum,NewExp,k);    //Record summary of at the end of each day: # of students in different condition
			
		}
		

	}
}
WriteDaySummaryFile();
}
