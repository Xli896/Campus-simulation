#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <map>
#include <string>
#include <sstream>
#include"Parameters_V5.h"
#include <random>

using namespace std;

class Class {
public:
	string CourseCode;
	double TranRate;
	double TranProb;
};

class Student {
public:
    int studentID;
	int condition;   //0 susceptible, 1 infected....
	int SE;  //the day that the student started being infected
	bool ifQuarantine; //if the student start quarantine during Symtomatic Phase
	bool ifOncampus;
	map<int,int> NumClasses; 
	double TransCoe;
	map<int,vector<Class*> > InClassToday;  //include all the courses the students will attend today
};

map<Class*,vector<Student*> > ClassStudentsTodayMap;
map<string,Class*> ClassMap; //Map the corresponding Class and its information via string(CourseCode)
map<int,Student*> StudentMap; //Map the corresponding Student and his/her information via int(StudentID)
vector<Student*> AllStudents; //All students vector
vector<Student*> StudentsOnCampus; //All students on campus vector
vector<Class*> AllClasses; //All Classes this semester
map<int,vector<Class*> > ClassesToday; //All classes today

int NSOn; //Total number of studentes live on campus in the semester
int TNS; //Total number of studentes in the semester
int TNC; //Total number of course in the semester
int CumuCase=0;
int CumuNumSym=0; //Total number of students have ever been symtomatically infected
vector<string> filenameAM;

string outputfilename="Average.csv";  //outputfile2: Day*Summary Matrix. record # of students in different health conditions on each day
std::ofstream DaySummary;

std::random_device rd;
std::default_random_engine ge(rd());
std::uniform_real_distribution<double> du(0.0,1.0);

string filenameAll="AffiliationMatrixAll.csv";
string filenameOnCampus="AffiliationMatrixOnCampus.csv";
bool OpenFiles() {
	std::ifstream comFileAll(filenameAll.c_str());
	if (!comFileAll.is_open()) {
		cerr << "error opening file" << endl;
	}
    string headers;
	string omit;
	string ID,classname;
	getline(comFileAll,omit,',');
	getline(comFileAll,headers);
	stringstream CC(headers);
	while(getline(CC,classname,','))
    {
        Class* c=new Class();
        if (classname[classname.size()-1]=='\r') {classname.erase(classname.end()-1);}
        AllClasses.push_back(c);
        c->CourseCode=classname;
        ClassMap[classname]=c;	
    }

	while(getline(comFileAll,headers))
	{
		stringstream ss(headers);
		getline(ss,ID,',');
		if (ID[ID.size()-1]=='\r') {ID.erase(ID.end()-1);}
		Student* s=new Student();
		s->studentID=stoi(ID);
		s->ifOncampus=0;
		double RandomNumber = du(ge);
		if(RandomNumber<=PR) {s->condition=5;}
		if(RandomNumber>PR) {s->condition=0;}
	    AllStudents.push_back(s);
	    StudentMap[stoi(ID)]=s;		
	}
	comFileAll.close();
	
	std::ifstream comFile(filenameOnCampus.c_str());
	if (!comFile.is_open()) {
		cerr << "error opening file" << endl;
	}
	getline(comFile,headers);
	while(getline(comFile,headers))
	{
		stringstream ss(headers);
		getline(ss,ID,',');
		Student* stu=StudentMap[stoi(ID)];
		stu->ifOncampus=1;
		StudentsOnCampus.push_back(stu);	
	}
	comFile.close();
	
	TNS=AllStudents.size();
	TNC=AllClasses.size();
	NSOn=StudentsOnCampus.size();
	cout<<"Total Number of Students"<<' ';  cout<<TNS<<endl;
	cout<<"Total Number of Students Oncampus"<<' ';  cout<<NSOn<<endl;
	cout<<"Total Number of Courses"<<' ';  cout<<TNC<<endl;
	
	return 0;
}





