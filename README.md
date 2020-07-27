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

`AffiliationMatrix.csv` / `AffiliationMatrixAll.csv` includes the assignment of all courses for all students, which is generated from the 2019 Fall registration data.

`AffiliationMatrixOnCampus.csv` includes the assignment of all courses for all students living on campus, which is depended on the course scheduling strategy and housing scenario.

`AffiliationMatrix_M/T/W/R/F/S.csv` includes the assignment of courses for students each weekday from Monday to Saturday respectively.

### Output Files

`Average.csv` shows the average results , which have # Cumulative Cases, # New Cases, # Quarantine  


### Different versions of simulation model

**1\.Version 1:** since the timeslots are fixed, the timeslot of the section should be same as 2019.


**2\. New sets added:**

`n_rf`: capacity of room r under safe distance f

`S_x`: the set of students choosing section x.

`p_x`: class size of section x.

`X_wo_room`: a set of sections that have no room assignment in 2019 fall

`X_wo_time`: a set of sections that have no time assignment in 2019 fall

`F:` Safe distance level `[0, 6, 8, 12]`

`k_f:` risk factors when not achieve f safe distance. `{0:10000,6:20,8:10,12:5}`

### assignment\_opt.py

Room assignment optimization model.
