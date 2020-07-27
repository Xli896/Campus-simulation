#include <iostream>
#include<cmath>
#include"Openclassfile.h"
#include"WriteOutput.h"
#include"StateTransition.h"
#include"CalculateProb.h"


int main() {
	filenameAM.push_back("AffiliationMatrix_M.csv");
	filenameAM.push_back("AffiliationMatrix_T.csv");
	filenameAM.push_back("AffiliationMatrix_W.csv");
	filenameAM.push_back("AffiliationMatrix_R.csv");
	filenameAM.push_back("AffiliationMatrix_F.csv");
	filenameAM.push_back("AffiliationMatrix_S.csv");
	filenameAM.push_back("AffiliationMatrix.csv");
	for(int i=filenameAM.size()-1;i>=0;i--) {Openclassfile(filenameAM[i],i);} //Read AffiliationMatrix and save the data

	double RandomNumber = du(ge); //Randomly generate Patient Zero
	allStudent[StudentVector[(int)(RandomNumber*NS)]]->condition=1;  
	allStudent[StudentVector[(int)(RandomNumber*NS)]]->SE=0;
	
	WriteDayStudentMatrix(0); //Day 0(record initial condition )
	WriteDaySummaryMatrix(CumuNumSym,0,1); 
	
	
	string output1="output1.csv";  
	std::ofstream OutPut1;
	OutPut1.open(output1,std::ios::app);
	    OutPut1<<"NIs"<<','; 
	    OutPut1<<"NIp"<<','; 
	    OutPut1<<"NIa"<<','; 
	    OutPut1<<"p"<<'\r';
	
	for(int i=0; i<NumberofWeeks;i++) //NumberofWeeks: 14 weeks in a semester
	{
		for(int j=0;j<DaysoftheWeek;j++)//DaysoftheWeek: 7 days in a week
		{
			int DayNum=7*i+j+1;//the number of that day 
			int NewExp=0; //#New Exposed
			vector<Class*> ClassSuc; //Susceptible class with infected student (not quarantine) at that day
			vector<Student*> StudentSuc; //Students those taking classes together with infected student  (not quarantine) at that day
			vector<Student*> StudentInfected; //Record students those have been exposed/infected and haven't recovered/Dead:  E,Ip,Ia,Is,Ih calculate transitions
			
			//Update StudentInfected at the beginning of each day 
			for (auto it = allStudent.begin(); it != allStudent.end(); it++)
			{
				if ( (it->second->condition==1)||(it->second->condition==2)||(it->second->condition==3)||(it->second->condition==4)||(it->second->condition==6) )
				{
					StudentInfected.push_back(it->second);
				}
			}
			
			//Update condition of those StudentInfected 
			StateTransition(StudentInfected,DayNum);
			
			if(j==DaysoftheWeek-1)  // Calculate the infection on Weekends
			{
				int TNIp=0;  //Total Number of infected students on campus: Ip, Ia, Is
				int TNIa=0;
				int TNIs=0;
				
				for (auto it = allStudent.begin(); it != allStudent.end(); it++)
				{
				    switch(it->second->condition){
					    case 0:  {
							StudentSuc.push_back(it->second);
							break;
					    }
					    case 1:  {break;}
					    case 5:  {break;}
					    case 6:  {break;}
					    case 7:  {break;}
					    case 2:  {TNIp=TNIp+1;break;}
					    case 3:  {TNIa=TNIa+1;break;}
					    case 4:  {TNIs=TNIs+1;break;}
				    }
				}
				double PW=CalculatePW(TNIp,TNIa,TNIs,NS,NW,epsilon_cw); //update PW (probability of infected on weekends) according to TNI and NS
				for (Student* it: StudentSuc)
				{
				    if(it->condition==0){
					     double RandomNumber = du(ge);
					     if(RandomNumber<=PW) {it->condition=1; it->SE=DayNum;NewExp=NewExp+1;}
				    }
				}
			}
						
			if(j!=DaysoftheWeek-1) //Calculate new infections during WeekDay (have classes on campus)
			{
				for (auto it1 = allClass.begin(); it1 != allClass.end(); it1++)
			    {
				    if((it1->second->NI!=0)&&(it1->second->DayoftheWeek[j]==1))
				    {
					    int NIs=0;
					    int NIp=0;
					    int NIa=0;
					    ClassSuc.push_back(it1->second);
					    for (Student* it2:classStudentMap[it1->second]) 
					    {
						    switch(it2->condition){
							    case 0:  
								{
									if( std::find(StudentSuc.begin(), StudentSuc.end(), it2) == StudentSuc.end() )
									{StudentSuc.push_back(it2);}
									break;
							    }
							    case 1:  {break;}
							    case 5:  {break;}
							    case 6:  {break;}
							    case 7:  {break;}
							    case 2:  {NIp=NIp+1;break;}
							    case 3:  {NIa=NIa+1;break;}
							    case 4:  {NIs=NIs+1;break;}
						    }
					    }
					    it1->second->p=Calculatep(NIs,NIp,NIa,epsilon_c); 
					    it1->second->q=Calculateq(it1->second->p,it1->second->NI,it1->second->NT,N); 
					    //string output1="output1.csv";  
						std::ofstream OutPut1;
					    OutPut1.open(output1,std::ios::app);
					    OutPut1<<NIs<<','; 
					    OutPut1<<NIp<<','; 
					    OutPut1<<NIa<<','; 
					    OutPut1<<it1->second->p<<',';
					    OutPut1<<it1->second->q<<'\r';
				    }
			    }
			    if (StudentSuc.size()!=0) 
			    {
				    for (Student* it1:StudentSuc)
				    {
					    double ProInf=0; //Probability of getting infected
					    double RateInf=0; //rate of infection
					    for (Class* it2:it1->InClass)
					    {
						    //cout<<it2->q<<endl;
						    RateInf=RateInf-log(1-it2->q);	
					    }
					    ProInf=1-exp(-RateInf);
					    //cout<<RateInf<<endl;
					    //cout<<ProInf<<endl;
					    double RandomNumber = du(ge);
					    if(RandomNumber<=ProInf)
					    {
						    it1->condition=1;
						    it1->SE=DayNum;
						    NewExp=NewExp+1;
					    }
				    }
			    }
			}
			
			WriteDayStudentMatrix(DayNum);    //Record condition of all students at the end of each day
			WriteDaySummaryMatrix(CumuNumSym,DayNum,NewExp);    //Record summary of at the end of each day: # of students in different condition
			
			/*cout<<"no problem"<<endl;
			cout<<ClassSuc.size()<<endl;
			cout<<StudentSuc.size()<<endl;
			cout<<StudentInfected.size()<<endl;
			cout<<'\n'<<endl;*/
			
		}
		

	}
}
