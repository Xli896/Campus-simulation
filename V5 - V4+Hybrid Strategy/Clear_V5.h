#include <iostream>
using namespace std;

bool ClearEachRun() {
	CumuCase=0;
	CumuNumSym=0; 
    for (Student* s:AllStudents) 
    {
	    double RandomNumber = du(ge);
	    if(RandomNumber<=PR) {s->condition=5;}
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