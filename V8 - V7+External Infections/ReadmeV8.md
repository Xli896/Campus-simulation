# Version 8

-----
Aug-12
-----

## `8.1` Simulation code for hybrid strategies 

Input Files:

Eight affiliation matrixes for strategies with hybrid mode

AffiliationMatrixAll.csv & AffiliationMatrix_M/T/W/R/F/S.csv & AffiliationMatrixOnCampus.csv

## `8.2` Simulation code for no hybrid strategies 

Input Files:

Seven affiliation matrixes for strategies without hybrid mode

AffiliationMatrix.csv & AffiliationMatrix_M/T/W/R/F/S.csv

## `8.3` Calibration code 

Input Files: 

Seven affiliation matrixes for Fall 2019 strategy (all courses are residential)

AffiliationMatrix.csv & AffiliationMatrix_M/T/W/R/F/S.csv

### Infection models included:

Calculate new infections in each class based on transmission rate and total number of infected students in the class

Calculate new infections outside of class based on transmission rate and total number of infected students in school

Calculate new infections introduced from the external source based on a constant rate of external infection

Calculate new infections through social activities on Thursday, Friday, and Saturday via Sampling 30 students contacted with each student during 3 hours

Calculate new infections on Sunday via Sampling NW students contacted with each student each day

### Interventions included:

Wearing masks;  Testing;  Contact tracing;  Quarantine

### Descriptions of each file

**1\. Main_V8.cpp:**

`0`- `S`:   Susceptible: Healthy and susceptible to the coronavirus

`1`- `E`:   Exposed: Have already exposed to the coronavirus but haven't become infectious for others

### Parameters_V8.h

`AffiliationMatrix.csv` / `AffiliationMatrixAll.csv` includes the assignment of all courses for all students, which is generated from the 2019 Fall registration data

### AllSchedule_V8.h

`AffiliationMatrix.csv` / `AffiliationMatrixAll.csv` includes the assignment of all courses for all students, which is generated from the 2019 Fall registration data

### EverydaySchedule_V8.h

`AffiliationMatrix.csv` / `AffiliationMatrixAll.csv` includes the assignment of all courses for all students, which is generated from the 2019 Fall registration data

### AllSchedule_V8.h

`AffiliationMatrix.csv` / `AffiliationMatrixAll.csv` includes the assignment of all courses for all students, which is generated from the 2019 Fall registration data

### AllSchedule_V8.h

`AffiliationMatrix.csv` / `AffiliationMatrixAll.csv` includes the assignment of all courses for all students, which is generated from the 2019 Fall registration data

### AllSchedule_V8.h

`AffiliationMatrix.csv` / `AffiliationMatrixAll.csv` includes the assignment of all courses for all students, which is generated from the 2019 Fall registration data
