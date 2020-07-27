#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <map>
#include <string>
#include <sstream>
#include <random>


using namespace std;



bool StateTransition(vector<Student*>& StudentInfected,int NumToday) 
{
    for(Student* stu: StudentInfected)
   {
	    switch(stu->condition)
	    { 
		    case 1:  {
				if (NumToday-(stu->SE)==ED){
				    stu->condition=2;
				    //for (Class* it2:it1->InClass) {it2->NI=it2->NI+1;} 
				}
				break;
			}
			
		    case 2:  {
				if (NumToday-(stu->SE)==PD+ED){
					double RandomNumber = du(ge);
					if(RandomNumber<=PA){
						stu->condition=3;
					}
					if(RandomNumber>PA){
						stu->condition=4;
						CumuNumSym=CumuNumSym+1;
						double RandomNumber = du(ge);
						if(RandomNumber<=PQ) {
							stu->ifQuarantine=(bool) 1; 
							//for (Class* it2:it1->InClass) {it2->NI=it2->NI-1;it2->NT=it2->NT-1;} 
						}
						if(RandomNumber>PQ) { stu->ifQuarantine=(bool) 0;  }
					}
				}
				break;
			}
			
			case 3:  {
				if (NumToday-(stu->SE)==PD+ED+AD){
				    stu->condition=5;
				    //for (Class* it2:it1->InClass) {it2->NI=it2->NI-1;} 
				}
				break;
			}
			
			case 4:  {
				if (NumToday-(stu->SE)==ED+PD+SD){
					double RandomNumber = du(ge);
					if(RandomNumber<=PH){
						stu->condition=6;
						/*if(!it1->ifQuarantine) {
							for (Class* it2:it1->InClass) {it2->NI=it2->NI-1;it2->NT=it2->NT-1;} 
						}*/
					}
					if(RandomNumber>PH){
						stu->condition=5;
						/*if(it1->ifQuarantine){
							for (Class* it2:it1->InClass) {it2->NT=it2->NT+1;} 
						}
						if(!it1->ifQuarantine){
							for (Class* it2:it1->InClass) {it2->NI=it2->NI-1;} 
						}*/
					}
				}
				break;
			}
			
			case 6:  {
				if (NumToday-(stu->SE)==ED+PD+SD+HD){
					double RandomNumber = du(ge);
					if(RandomNumber<=PDE){
						stu->condition=7;
						TNS=TNS-1;
						NSOn=NSOn-1;
					}
					if(RandomNumber>PDE){
						stu->condition=5;
						//for (Class* it2:it1->InClass) {it2->NT=it2->NT+1;} 
					}
				}
				break;
			}								
		}
   }
	return 0;
}