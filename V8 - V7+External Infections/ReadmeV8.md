# Campus-simulation

-----
July-26
-----

### Symbols' Description

`0`- `S`:   Susceptible: Healthy and susceptible to the coronavirus

`1`- `E`:   Exposed: Have already exposed to the coronavirus but haven't become infectious for others

`2`- `Ip`:  Pre-symptomatically infected: During infectious period before showing symptoms

`3`- `Ia`:  Asymptomatically infected: Being infectious but showing no symptoms

`4`- `Is`:  Symptomatically infected: Being infectious and have started showing symptoms

`5`- `R`:   Recovered: Have already recovered from COVID-19, thus have an antibody for now

`6`- `Ih`:  Hospitalization: Be in hospitalized after being symtomatically infected 

`7`- `D`:   Dead

`10`- `RP`: Have recovered from COVID-19 thus have an antibody before the beginning of the semester


### Input Files

`AffiliationMatrix.csv` / `AffiliationMatrixAll.csv` includes the assignment of all courses for all students, which is generated from the 2019 Fall registration data

`AffiliationMatrixOnCampus.csv` includes the assignment of all courses for all students living on campus, which is depended on the course scheduling strategy and housing scenario

`AffiliationMatrix_M/T/W/R/F/S.csv` includes the assignment of courses for students each weekday from Monday to Saturday respectively

### Output Files
