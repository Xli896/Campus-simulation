## Version 8

### `Folder 8.1` Simulation code for hybrid strategies 

Input Files:

Eight affiliation matrixes for strategies with hybrid mode

AffiliationMatrixAll.csv & AffiliationMatrix_M/T/W/R/F/S.csv & AffiliationMatrixOnCampus.csv


### `Folder 8.2` Simulation code for no hybrid strategies 

Input Files:

Seven affiliation matrixes for strategies without hybrid mode

AffiliationMatrix.csv & AffiliationMatrix_M/T/W/R/F/S.csv


### `Folder 8.3` Calibration code 

Input Files: 

Seven affiliation matrixes for Fall 2019 strategy (all courses are residential)

AffiliationMatrix.csv & AffiliationMatrix_M/T/W/R/F/S.csv


### `Model Features` Interventions included:

Intervention 1: Wearing masks

Intervention 2: Testing

Intervention 3: Contact tracing

Intervention 4: Quarantine


### `Model Features` Infection models included:

Calculate new infections in each class based on transmission rate and total number of infected students in the class

Calculate new infections outside of class based on transmission rate and total number of infected students in school

Calculate new infections introduced from the external source based on a constant rate of external infection

Calculate new infections on Thursday, Friday, and Saturday via Sampling 30 students contacted with each student during 3 hours

Calculate new infections on Sunday via Sampling NW students contacted with each student each day


### `Code Introduction` Descriptions of each function file

**1\. Main_V8.cpp:**

`0`- `S`:   Susceptible: Healthy and susceptible to the coronavirus

`1`- `E`:   Exposed: Have already exposed to the coronavirus but haven't become infectious for others

**2\. Parameters_V8.h:**

`AffiliationMatrix.csv` / `AffiliationMatrixAll.csv` includes the assignment of all courses for all students, which is generated from the 2019 Fall registration data

**3\. AllSchedule_V8.h:**

`AffiliationMatrix.csv` / `AffiliationMatrixAll.csv` includes the assignment of all courses for all students, which is generated from the 2019 Fall registration data

**4\. EverydaySchedule_V8.h:**

`AffiliationMatrix.csv` / `AffiliationMatrixAll.csv` includes the assignment of all courses for all students, which is generated from the 2019 Fall registration data

**5\. Write_V8.h:**

`AffiliationMatrix.csv` / `AffiliationMatrixAll.csv` includes the assignment of all courses for all students, which is generated from the 2019 Fall registration data

**6\. StateTransition_V8.h:**

`AffiliationMatrix.csv` / `AffiliationMatrixAll.csv` includes the assignment of all courses for all students, which is generated from the 2019 Fall registration data

**7\. TransmissionInfections_V8.h:**

`AffiliationMatrix.csv` / `AffiliationMatrixAll.csv` includes the assignment of all courses for all students, which is generated from the 2019 Fall registration data

**8\. SamplingInfectionsWeekends_V8.h:**

`AffiliationMatrix.csv` / `AffiliationMatrixAll.csv` includes the assignment of all courses for all students, which is generated from the 2019 Fall registration data

**9\. SampleInfectionsWeekdays_V8.h:**

`AffiliationMatrix.csv` / `AffiliationMatrixAll.csv` includes the assignment of all courses for all students, which is generated from the 2019 Fall registration data

**10\. Sample_V8.h:**

`AffiliationMatrix.csv` / `AffiliationMatrixAll.csv` includes the assignment of all courses for all students, which is generated from the 2019 Fall registration data

**11\. TestingProcess_V8.h:**

`AffiliationMatrix.csv` / `AffiliationMatrixAll.csv` includes the assignment of all courses for all students, which is generated from the 2019 Fall registration data

**12\. ContactsTracing_V8.h:**

`AffiliationMatrix.csv` / `AffiliationMatrixAll.csv` includes the assignment of all courses for all students, which is generated from the 2019 Fall registration data

**13\. Clear_V8.h:**

`AffiliationMatrix.csv` / `AffiliationMatrixAll.csv` includes the assignment of all courses for all students, which is generated from the 2019 Fall registration data

