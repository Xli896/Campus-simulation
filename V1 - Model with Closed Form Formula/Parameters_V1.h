#include <iostream>
#define DaysoftheWeek 7
#define NumberofWeeks 14


int N=6; //Number of students to sit within effective infectious distance within a classroom
int epsilon_c=1;// The susceptibility of the population of students in a classroom
int epsilon_cw=1; // The susceptibility of the population of students on weekends
int NW=6; //Number of students to contact with effective infectious distance on weekends
float PR=0.07; // % of residents with antibody at Georgia State: 7.1 percent

//Parameters used for SEIR model
int ED=5;  //Exposed duration: the time (days) it takes for an exposed individual to move from E to Ip
int PD=1;  //Pre-symptomatic duration: The time (days) before an infected patient enters either asymptomatic and symptomatic phases	
int SD=3;  //Symptomatic duration
int AD=2;  //Asymptomatic duration
int HD=10;  //Hospitalized duration
float PQ=0.5; //Probability of qurantine if a student start showing symptom
float PS=0.66;  //Probability of Symptomatic
float PA=0.34;  //Probability of Asymptomatic
float PH=0.143;   //Probability of Hospitalization
float PDE=0.0515;  //Probability a person who is hospitalized dies


//float STA=1.5;   //Symptomatic-to-Asymptomatic duration ratio
//float RTD=9.9;   //Recover-to-Death ratio
//quarantine for state S and H 
//float p=0.005; //Probability of getting infected by a student j given they share a class together and social distance

