#include <iostream>
using namespace std;

bool ClearEachRun() {
	CumuCase=0;
	CumuNumSym=0; 
	CumuQua=0;
    for (Student* s:AllStudents) 
    {
	    s->ifQuarantine=0;
	    s->ifTested=0;
	    s->ifWaitResult=0;
	    s->ifPositive=0;
	    s->TestPriority=1;
	    double RandomNumber = du(ge);
	    if(RandomNumber<=PR) {s->condition=10;}
	    if(RandomNumber>PR) {s->condition=0;}
    }
	return 0;
}

bool ClearEachDay() {
	for (Class* c:AllClasses) 
	{
	    c->TranRate=0;
	    c->TranProb=0;
	}
	ClassStudentsTodayMap.clear();
	return 0;
}