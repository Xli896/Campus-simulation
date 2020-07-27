#include <iostream>
#define DaysoftheWeek 7
#define NumberofWeeks 14

double lambda_s=0.015;
double beta=0.46;
double lambda_a=beta*lambda_s;
double lambda_p=beta*lambda_s;

double DiscountRate=0.05;
double Pa=0.7672*DiscountRate; //Infection probability for a susceptible student given he/she sit next to one asymptomatically infectious student
double Ps=0.95*DiscountRate;  //Infection probability for a susceptible student given he/she sit next to one symptomatically infectious student
double Pp=0.7672*DiscountRate; //Infection probability for a susceptible student given he/she sit next to one student in pre-infectious phase

int NW_L=25; //Number of students to contact with effective infectious distance on weekends
int NW_H=100;
double PGreekLife=0.25;
double PR=0.07; // % of residents with antibody at Georgia State: 7.1 percent
int Initial=4;
int RunTimes=50;

//Parameters used for SEIR model
int ED=5;  //Exposed duration: the time (days) it takes for an exposed individual to move from E to Ip
int PD=1;  //Pre-symptomatic duration: The time (days) before an infected patient enters either asymptomatic and symptomatic phases	
int SD=3;  //Symptomatic duration
int AD=2;  //Asymptomatic duration
int HD=10;  //Hospitalized duration
double PQ=0.5; //Probability of qurantine if a student start showing symptom
double PS=0.66;  //Probability of Symptomatic
double PA=0.34;  //Probability of Asymptomatic
double PH=0.143;   //Probability of Hospitalization
double PDE=0.0015;  //Probability a person who is hospitalized dies


//float STA=1.5;   //Symptomatic-to-Asymptomatic duration ratio
//float RTD=9.9;   //Recover-to-Death ratio
//quarantine for state S and H 
//float p=0.005; //Probability of getting infected by a student j given they share a class together and social distance

